#include "common.h"
#include "ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>
#include <curses.h>

int main(int argc, char **argv) {
    int ret;

    //check for shell
    ret = system(NULL);
    init_ui();

    if (ret) {
        add_msg("Shell is avalible");
    } else {
        add_msg("Shell is not avalible");
    }
    add_msg("testing 1");
    add_msg("testing 2");
    add_msg("testing 3");

    if (getuid()) {
        add_msg("Program not running as root, attempting to gain root privileges");

        ensure(setuid(0) != -1);

        add_msg("Root access obtained");
    }

    int ch;
    while((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 'a':
                add_msg("a key pressed");
                break;
            case 'f':
                add_msg("f key pressed");
                break;
            default:
                add_msg("key pressed");
                break;
        }
    }

    close_ui();
    return EXIT_SUCCESS;
}
