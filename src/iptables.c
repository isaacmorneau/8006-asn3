#include <string.h>
#include <stdlib.h>
#include "iptables.h"

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

