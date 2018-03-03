/*
 * HEADER FILE: epoll.h - Epoll setup and wrappers
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

#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>

#define MAX_EPOLL_EVENTS 64

int create_epoll_fd(void);
void add_epoll_fd(const int epollfd, const int sock, struct epoll_event *ev);
int wait_epoll_event(const int epollfd, struct epoll_event *events);

#endif

