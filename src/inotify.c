#include <sys/inotify.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "inotify.h"
#include "iptables.h"
#include "epoll.h"
#include "common.h"
#include "ui.h"

static const char *log_name = "/var/log/secure";

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: create_inotify_descriptor
 * Paramaters: void
 * Return: int - the inotify file descriptor
 * Notes: creates a file descriptor for inotify
 * */
int create_inotify_descriptor(void) {
    int fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    ensure(inotify_add_watch(fd, log_name, IN_MODIFY) != -1);
    return fd;
}

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: wait_for_logs
 * Paramaters:
 *      const int inot_fd -
 *      const int fail_max -
 *      const int timeout -
 *      const int daemon -
 * Return: void
 * Notes:
 * */
void wait_for_logs(const int inot_fd, const int fail_max, const int timeout, const int daemon) {
    int epollfd = create_epoll_fd();

    struct epoll_event ev;
    ev.data.fd = inot_fd;
    ev.events = EPOLLIN | EPOLLET;

    add_epoll_fd(epollfd, inot_fd, &ev);

    struct epoll_event *event_list;
    ensure((event_list = calloc(MAX_EPOLL_EVENTS, sizeof(struct epoll_event))) != NULL);

    unsigned char buf[sizeof(struct inotify_event) + NAME_MAX + 1];

    for (;;) {
        int n = wait_epoll_event(epollfd, event_list);
        for (int i = 0; i < n; ++i) {
            process_secure_logs(fail_max, timeout, daemon);
empty_inotify:
            ensure_nonblock(read(event_list[i].data.fd, buf, sizeof(buf)) != -1);
            if (errno == EAGAIN) {
                break;
            }
            //handle updated log file
            goto empty_inotify;
        }
    }

    free(event_list);
}

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: process_secure_logs
 * Paramaters:
 *      const int inot_fd -
 *      const int fail_max -
 *      const int timeout -
 *      const int daemon -
 * Return: void
 * Notes:
 * */
void process_secure_logs(const int fail_max, const int timeout, const int daemon) {
    struct stat st;
    ensure(stat(log_name, &st) == 0);

    size_t size = st.st_size;

    char command[1024];
    memset(command, 0, 1024);

    sprintf(command, "python src/format_data.py %d %d", fail_max, time(NULL) + timeout);

    FILE *result;
    ensure((result = popen(command, "r")) != NULL);

    char buffer[1025];
    char message[1024];
    while(fgets(buffer, 1024, result)) {
        char *ip = strchr(buffer, ' ') + 1;
        ip[strlen(ip) - 1] = '\0';
        memset(message, 0, 1024);
        sprintf(message, "%s %s\n", (buffer[0] == 'B') ? "Banning " : "Unbanning ", ip);
        if (!daemon) {
            add_msg(message);
        }
        if (buffer[0] == 'B') {
            //Ban ip
            block_ip(ip);
        } else {
            //Un-ban ip
            unblock_ip(ip);
        }
    }
    fclose(result);
}
