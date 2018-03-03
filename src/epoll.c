/*
 * SOURCE FILE: epoll.c - Implementation of functions declared in epoll.h
 *
 * PROGRAM: 8006-asn3
 *
 * DATE: March 3, 2018
 *
 * FUNCTIONS:
 * int create_epoll_fd(void);
 * void add_epoll_fd(const int epollfd, const int sock, struct epoll_event *ev);
 * int wait_epoll_event(const int epollfd, struct epoll_event *events);
 *
 * DESIGNER: John Agapeyev
 *
 * PROGRAMMER: John Agapeyev
 */
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "epoll.h"
#include "common.h"

/*
 * FUNCTION: create_epoll_fd
 *
 * DATE:
 * Dec. 2, 2017
 *
 * DESIGNER:
 * John Agapeyev
 *
 * PROGRAMMER:
 * John Agapeyev
 *
 * INTERFACE:
 * int create_epoll_fd(void);
 *
 * RETURNS:
 * int - The created epoll file descriptor
 */
int create_epoll_fd(void) {
    int efd;
    ensure((efd = epoll_create1(0)) != -1);
    return efd;
}

/*
 * FUNCTION: add_epoll_fd
 *
 * DATE:
 * Dec. 2, 2017
 *
 * DESIGNER:
 * John Agapeyev
 *
 * PROGRAMMER:
 * John Agapeyev
 *
 * INTERFACE:
 * void add_epoll_fd(const int epollfd, const int sock, struct epoll_event *ev);
 *
 * PARAMETERS:
 * const int epollfd - The epoll descriptor to add the socket to
 * const int sock - The socket to add to epoll
 * struct epoll_event *ev - The epoll_event struct saying how epoll should handle the socket
 *
 * RETURNS:
 * void
 */
void add_epoll_fd(const int epollfd, const int sock, struct epoll_event *ev) {
    ensure(epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, ev) != -1);
}

/*
 * FUNCTION: wait_epoll_event
 *
 * DATE:
 * Dec. 2, 2017
 *
 * DESIGNER:
 * John Agapeyev
 *
 * PROGRAMMER:
 * John Agapeyev
 *
 * INTERFACE:
 * int wait_epoll_event(const int epollfd, struct epoll_event *events);
 *
 * PARAMETERS:
 * const int epollfd - The epoll descriptor to wait on
 * struct epoll_event *events - The event list that epoll write too
 *
 * RETURNS:
 * int - The number of events on the epoll descriptor
 */
int wait_epoll_event(const int epollfd, struct epoll_event *events) {
    int nevents;
    ensure((nevents = epoll_wait(epollfd, events, MAX_EPOLL_EVENTS, -1)) != -1);
    return nevents;
}

