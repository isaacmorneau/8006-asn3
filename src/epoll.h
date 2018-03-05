#ifndef EPOLL_H
#define EPOLL_H
/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Notes: The functions for opening adding to and managing epoll structures
 * */

#include <sys/epoll.h>

#define MAX_EPOLL_EVENTS 64

int create_epoll_fd(void);
void add_epoll_fd(const int epollfd, const int sock, struct epoll_event *ev);
int wait_epoll_event(const int epollfd, struct epoll_event *events);

#endif

