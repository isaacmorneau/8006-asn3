/*
 * SOURCE FILE: epoll.c - Implementation of functions declared in epoll.h
 *
 * PROGRAM: 8006-asn3
 *
 * DATE: March 3, 2018
 *
 * FUNCTIONS:
 * int createEpollFd(void);
 * void addEpollSocket(const int epollfd, const int sock, struct epoll_event *ev);
 * int waitForEpollEvent(const int epollfd, struct epoll_event *events);
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
 * FUNCTION: createEpollFd
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
 * int createEpollFd(void);
 *
 * RETURNS:
 * int - The created epoll file descriptor
 */
int createEpollFd(void) {
    int efd;
    ensure((efd = epoll_create1(0)) != -1);
    return efd;
}

/*
 * FUNCTION: addEpollSocket
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
 * void addEpollSocket(const int epollfd, const int sock, struct epoll_event *ev);
 *
 * PARAMETERS:
 * const int epollfd - The epoll descriptor to add the socket to
 * const int sock - The socket to add to epoll
 * struct epoll_event *ev - The epoll_event struct saying how epoll should handle the socket
 *
 * RETURNS:
 * void
 */
void addEpollSocket(const int epollfd, const int sock, struct epoll_event *ev) {
    ensure(epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, ev) != -1);
}

/*
 * FUNCTION: waitForEpollEvent
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
 * int waitForEpollEvent(const int epollfd, struct epoll_event *events);
 *
 * PARAMETERS:
 * const int epollfd - The epoll descriptor to wait on
 * struct epoll_event *events - The event list that epoll write too
 *
 * RETURNS:
 * int - The number of events on the epoll descriptor
 */
int waitForEpollEvent(const int epollfd, struct epoll_event *events) {
    int nevents;
    ensure((nevents = epoll_wait(epollfd, events, MAX_EPOLL_EVENTS, -1)) != -1);
    return nevents;
}

