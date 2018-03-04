#include <sys/inotify.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "inotify.h"
#include "iptables.h"
#include "epoll.h"
#include "common.h"
#include "ui.h"

static const char *log_name = "/var/log/secure";

int create_inotify_descriptor(void) {
    int fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    ensure(inotify_add_watch(fd, log_name, IN_MODIFY) != -1);
    return fd;
}

void wait_for_logs(const int inot_fd) {
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
            ensure(event_list[i].events & ~EPOLLIN == 0);
empty_inotify:
            ensure_nonblock(read(event_list[i].data.fd, buf, sizeof(buf)) != -1);
            if (errno == EAGAIN) {
                continue;
            }
            //handle updated log file
            process_secure_logs();
            goto empty_inotify;
        }
    }

    free(event_list);
}

void process_secure_logs(void) {
    struct stat st;
    ensure(stat(log_name, &st) == 0);

    size_t size = st.st_size;

    //This command will need to be tweaked obviously
    FILE *result;
    ensure((result = popen("python format_data.py 100 10", "r")) != NULL);

    char buffer[1025];
    while(fgets(buffer, 1024, result)) {
        char *ip = strchr(buffer, ' ') + 1;
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
