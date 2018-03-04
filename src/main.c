#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>
#include <curses.h>
#include "common.h"
#include "ui.h"
#include "inotify.h"

int main(int argc, char **argv) {
    int ret;
    int attempt_limt = 3;
    int timelimit = 5;
    //check for shell
    ret = system(NULL);
    init_ui();

    if (ret) {
        add_msg("Shell is avalible");
    } else {
        add_msg("Shell is not avalible");
    }
    if (getuid()) {
        add_msg("Program not running as root, attempting to gain root privileges");

        ensure(setuid(0) != -1);

        add_msg("Root access obtained");
    }

    int ch;
    char input[256];
    while((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_F(2):
                add_msg("Starting...");
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
    }
    //TODO stuff???
    wait_for_logs(create_inotify_descriptor(), attempt_limt, timelimit);

    close_ui();
    return EXIT_SUCCESS;
}
