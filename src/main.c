#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>
#include <curses.h>
#include <getopt.h>
#include "common.h"
#include "ui.h"
#include "inotify.h"

#define SOCKOPTS "hda:t:"

static void print_help(void){
    puts("usage options:\n"
            "\t[t]ime - set the time limit\n"
            "\t[a]ttempt - set the attempt limt\n"
            "\t[d]aemon - set the attempt limt\n"
            "\t[h]elp - this message");
}

int main(int argc, char **argv) {
    int ret, c;
    int attempt_limt = 3;
    int timelimit = 5;
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
            add_msg("Shell is avalible");
        } else {
            add_msg("Shell is not avalible");
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
                    timelimit = atoi(input);
                    break;
                case KEY_F(4):
                    add_msg("Enter Timelimit: ");
                    get_msg(input, 256);
                    attempt_limt = atoi(input);
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

    wait_for_logs(create_inotify_descriptor(), attempt_limt, timelimit);


    if (!daemon)
        close_ui();
    return EXIT_SUCCESS;
}
