#ifndef COMMON_H
#define COMMON_H
/*
 * Author & Designer: Isaac Morneau
 * Date: 2018-03-05
 * Notes: holds common error handling wrappers for all syscalls
 * */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ncurses.h>

#define ensure(expr)\
    do {\
        if (!(expr)) {\
            endwin();\
            fprintf(stderr, "%s::%s::%d\n\t", __FILE__, __FUNCTION__, __LINE__);\
            perror(#expr);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

#define ensure_nonblock(expr)\
    do {\
        if (!(expr) && errno != EAGAIN && errno != EWOULDBLOCK) {\
            endwin();\
            fprintf(stderr, "%s::%s::%d\n\t", __FILE__, __FUNCTION__, __LINE__);\
            perror(#expr);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

#endif
