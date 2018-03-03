#include <sys/inotify.h>
#include <stdlib.h>
#include <stdio.h>
#include "inotify.h"
#include "common.h"

int create_inotify_descriptor(void) {
    int fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    ensure(inotify_add_watch(fd, "/var/log/secure", IN_MODIFY) != -1);
    return fd;
}


