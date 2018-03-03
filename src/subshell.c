#include "subshell.h"
#include "common.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int pid = 0;
FILE * childstdin;
char procpath[256];

void init_subshell() {
    ensure((pid = fork()) != -1);
    switch (pid){
        case 0://child
            execl("/bin/bash", "/bin/bash", (char *)0);
            break;
        default://parrent
            sprintf(procpath, "/proc/%d/fd/0", pid);
            childstdin = fopen(procpath, "w");
            break;
    }
}

void close_subshell() {
    ensure(!kill(pid, SIGTERM));
    ensure(wait(0) != -1);
    fclose(childstdin);
}

void subshell_run(const char * restrict command) {
    fputs(command, childstdin);
}
