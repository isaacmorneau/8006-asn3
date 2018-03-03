#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//ip must be null-terminated, and contain the ip to block as a string
void block_ip(const char *restrict ip) {
    const char *input   = "iptables -A INPUT ";
    const char *output  = "iptables -A OUTPUT ";
    const char *forward = "iptables -A FORWARD ";
    const char *drop = " -j DROP";

    char command[strlen(forward) + strlen(ip) + strlen(drop) + 1];
    strcat(command, input);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, output);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, forward);
    strcat(command, ip);
    strcat(command, drop);

    system(command);
}

//ip must be null-terminated, and contain the ip to block as a string
void unblock_ip(const char *restrict ip) {
    const char *input   = "iptables -D INPUT ";
    const char *output  = "iptables -D OUTPUT ";
    const char *forward = "iptables -D FORWARD ";
    const char *drop = " -j DROP";

    char command[strlen(forward) + strlen(ip) + strlen(drop) + 1];
    strcat(command, input);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, output);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, forward);
    strcat(command, ip);
    strcat(command, drop);

    system(command);
}

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
