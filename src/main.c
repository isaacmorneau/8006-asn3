#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>

#define COMMAND_WIDTH 40
#define NCURSES_BULLSHIT_INIT refresh()

int main(int argc, char **argv) {
    WINDOW * command_window, * info_window;
    int ret;
    //start up ncurses and setup key handling
    initscr();
    raw();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    NCURSES_BULLSHIT_INIT;

    command_window = newwin(LINES, COMMAND_WIDTH, 0, 0);
    //command_window = newwin(LINES, COMMAND_WIDTH, 0, 0);
    info_window = newwin(LINES, COLS - COMMAND_WIDTH - 2, 0, COMMAND_WIDTH + 1);
    //info_window = newwin(LINES, COLS - COMMAND_WIDTH - 1, 0, COMMAND_WIDTH + 1);

    box(command_window, 0, 0);
    box(info_window, 0, 0);

    wrefresh(command_window);
    wrefresh(info_window);

    //check for shell
    ret = system(NULL);
    mvwprintw(info_window, 1, 1, "Shell is%s avalible\n", ret ? "" : " not");
    wrefresh(info_window);

    if (getuid()) {
        mvwprintw(info_window, 2, 1, "Program not running as root, attempting to gain root privileges\n");
        wrefresh(info_window);

        ensure(setuid(0) != -1);

        mvwprintw(info_window, 3, 1, "Root access obtained\n");
        wrefresh(info_window);
    }

    mvwprintw(command_window, 1, 1, "F1 - Exit");
    wrefresh(command_window);

    //block waiting for a key
    wrefresh(command_window);
    wrefresh(info_window);
    int ch;
    while((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            default:
                break;
        }
    }

    //for the love of god dont break the whole terminal if it worked as expected
    delwin(info_window);
    delwin(command_window);
    endwin();
    return EXIT_SUCCESS;
}
