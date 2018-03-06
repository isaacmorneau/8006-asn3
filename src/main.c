#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>
#include <curses.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/signal.h>
#include "common.h"
#include "ui.h"
#include "inotify.h"

#define SOCKOPTS "hda:t:"

/*
 * Author & Designer: Isaac Morneau
 * Date: 2018-03-05
 * Function: print_help
 * Paramaters: void
 * Return: void
 * Notes: prints usage information
 * */
static void print_help(void){
    puts("usage options:\n"
            "\t-[-t]ime <seconds; default 1 day; -1 for infinite>- set the time limit\n"
            "\t-[-a]ttempt <default 3> - set the attempt limt\n"
            "\t-[-d]aemon - set the attempt limt\n"
            "\t-[-h]elp - this message");
}

/*
 * Author & Designer: Isaac Morneau
 * Date: 2018-03-05
 * Function: main
 * Paramaters: int argc - the number of arguments
 *      char **argv - the array of string arguments
 * Return: int - the return code of the program
 * Notes: parses the arguments and starts either a UI or a daemon
 * */
int main(int argc, char **argv) {
    int ret, c;
    //default 3 trys before timeout
    int attempt_limt = 3;
    //default one day timeout
    int timelimit = 86400;
    int daemon = 0;

    while (1) {
        int option_index = 0;

        static struct option long_options[] = {
            {"help",    no_argument,       0, 'h' },
            {"daemon",  no_argument,       0, 'd' },
            {"attempt", required_argument, 0, 'a' },
            {"time",    required_argument, 0, 't' },
            {0,         0,                 0, 0   }
        };

        c = getopt_long(argc, argv, SOCKOPTS, long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'a':
                attempt_limt = atoi(optarg);
                break;
            case 't':
                timelimit = atoi(optarg);
                break;
            case 'd':
                daemon = 1;
                break;
            case 'h':
            case '?':
            default:
                print_help();
                return 0;
        }
    }

    //check for shell
    ret = system(NULL);
    if (!daemon)
        init_ui();

    if (!daemon) {
        if (ret) {
            add_msg("Shell is available");
        } else {
            add_msg("Shell is not available");
        }
    }

    if (getuid()) {
        if (!daemon)
            add_msg("Program not running as root, attempting to gain root privileges");

        ensure(setuid(0) != -1);

        if (!daemon)
            add_msg("Root access obtained");
    }

    if (!daemon) {
        int ch;
        char input[256];
        while((ch = getch()) != KEY_F(1)) {
            switch (ch) {
                case KEY_F(2):
                    add_msg("Starting...");
                    ch = 0;
                    break;
                case KEY_F(3):
                    add_msg("Enter Attempt Limit: ");
                    get_msg(input, 256);
                    attempt_limt = atoi(input);
                    break;
                case KEY_F(4):
                    add_msg("Enter Timelimit: ");
                    get_msg(input, 256);
                    timelimit = atoi(input);
                    break;
                default:
                    //if its not recognized just ignore it
                    break;
            }
            if (!ch) {
                break;
            }
        }
    }

    if (daemon) {
        pid_t pid;
        pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);
        if (pid > 0)
            exit(EXIT_SUCCESS);

        if (setsid() < 0)
            exit(EXIT_FAILURE);

        signal(SIGCHLD, SIG_IGN);
        signal(SIGHUP, SIG_IGN);

        pid = fork();

        if (pid < 0)
            exit(EXIT_FAILURE);
        if (pid > 0)
            exit(EXIT_SUCCESS);
        umask(0);
        chdir("/");
        for (int x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
            close (x);
        }
    }

    system("iptables -F");
    system("iptables -X");
    system("rm /tmp/8006/* >/dev/null 2>/dev/null");

    wait_for_logs(create_inotify_descriptor(), attempt_limt, timelimit, daemon);

    if (!daemon)
        close_ui();
    return EXIT_SUCCESS;
}
