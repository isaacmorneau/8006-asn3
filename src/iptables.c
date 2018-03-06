#include <string.h>
#include <stdlib.h>
#include "iptables.h"
#include "ui.h"

const char *add   = "iptables -A ";
const char *delete   = "iptables -D ";
const char *source   = "-s ";
const char *dest   = "-d ";
const char *input   = "INPUT ";
const char *output  = "OUTPUT ";
const char *forward = "FORWARD ";
const char *drop = " -j DROP 2> /dev/null";

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: block_ip
 * Paramaters:
 *          const char *restrict ip - The ip address to block
 * Return: void
 * Notes: Blocks both source and destination traffic for the ip
 * */
void block_ip(const char *restrict ip) {
    char command[strlen(add) + strlen(forward) + strlen(source) + strlen(ip) + strlen(drop) + 1];
    memset(command, 0, sizeof(command));
    strcat(command, add);
    strcat(command, input);
    strcat(command, source);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, add);
    strcat(command, output);
    strcat(command, source);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));
    strcat(command, add);
    strcat(command, forward);
    strcat(command, source);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, add);
    strcat(command, input);
    strcat(command, dest);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, add);
    strcat(command, output);
    strcat(command, dest);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));
    strcat(command, add);
    strcat(command, forward);
    strcat(command, dest);
    strcat(command, ip);
    strcat(command, drop);

    system(command);
}

/*
 * Author & Designer: John Agapeyev
 * Date: 2018-03-05
 * Function: unblock_ip
 * Paramaters:
 *          const char *restrict ip - The ip address to unblock
 * Return: void
 * Notes: Unblocks both source and destination traffic for the ip
 * */
void unblock_ip(const char *restrict ip) {
    char command[strlen(drop) + strlen(forward) + strlen(source) + strlen(ip) + strlen(drop) + 1];
    memset(command, 0, sizeof(command));
    strcat(command, delete);
    strcat(command, input);
    strcat(command, source);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, delete);
    strcat(command, output);
    strcat(command, source);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));
    strcat(command, delete);
    strcat(command, forward);
    strcat(command, source);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, delete);
    strcat(command, input);
    strcat(command, dest);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));

    strcat(command, delete);
    strcat(command, output);
    strcat(command, dest);
    strcat(command, ip);
    strcat(command, drop);

    system(command);

    memset(command, 0, sizeof(command));
    strcat(command, delete);
    strcat(command, forward);
    strcat(command, dest);
    strcat(command, ip);
    strcat(command, drop);

    system(command);
}

