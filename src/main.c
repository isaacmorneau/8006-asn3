#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
    int ret;

    //check for shell
    ret = system(0);
    printf("Shell is%s avalible\n", ret ? "" : " not");

    if (getuid()) {
        printf("Program not running as root, attempting to gain root privileges\n");
        if (setuid(0) == -1) {
            if (errno == EPERM) {
                printf("Insufficient permissions, exiting...\n");
                return EXIT_FAILURE;
            }
            perror("setuid");
            return EXIT_FAILURE;
        }
        printf("Root access obtained\n");
    }

    return EXIT_SUCCESS;
}
