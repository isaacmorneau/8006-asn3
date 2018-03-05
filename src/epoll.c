#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "epoll.h"
#include "common.h"

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: create_epoll_fd
 * Paramaters: void
 * Return: int - the epoll file descriptor
 * Notes: creates a file descriptor for epoll
 * */
int create_epoll_fd(void) {
    int efd;
    ensure((efd = epoll_create1(0)) != -1);
    return efd;
}

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: add_epoll_fd
 * Paramaters:
 *      const int epollfd - The epoll descriptor to add the socket to
 *      const int sock - The socket to add to epoll
 *      struct epoll_event *ev - The epoll_event struct saying how epoll should handle the socket
 * Return: void
 * Notes: adds a file descriptor with an event to a epoll struct
 * */
void add_epoll_fd(const int epollfd, const int sock, struct epoll_event *ev) {
    ensure(epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, ev) != -1);
}

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: wait_epoll_event
 * Paramaters:
 *      const int epollfd - the epoll descriptor to wait on
 *      struct epoll_event *events - the buffer to return the events un
 * Return: int - the number of events returned
 * Notes: waits for events on the specified epoll descriptor
 * */
int wait_epoll_event(const int epollfd, struct epoll_event *events) {
    ensure(epoll_wait(epollfd, events, MAX_EPOLL_EVENTS, 1000) != -1);
    return 1;
}

