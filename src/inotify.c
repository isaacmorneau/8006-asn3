#include <sys/inotify.h>
#include <stdlib.h>
#include <stdio.h>
#include "inotify.h"

int create_inotify_descriptor(void) {
    int fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    if (inotify_add_watch(fd, "/var/log/secure", IN_MODIFY) == -1) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }
    return fd;
}


