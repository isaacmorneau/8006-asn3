#include "ui.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_WIDTH 40
#define NCURSES_BULLSHIT_INIT refresh()

WINDOW * command_window, * info_window;
char ** mega_buffer;

int write_width = 0;
int write_height = 0;

void init_ui() {
    //start up ncurses and setup key handling
    initscr();
    raw();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    NCURSES_BULLSHIT_INIT;

    write_width = COLS - COMMAND_WIDTH - 2;
    write_height = LINES - 2;

    command_window = newwin(LINES, COMMAND_WIDTH, 0, 0);
    info_window = newwin(LINES, write_width, 0, COMMAND_WIDTH + 1);

    //allocate a grid for the output buffer
    mega_buffer = (char **)calloc(1, sizeof(char*)*write_height);
    for (int i = 0;i < write_height; ++i)
        mega_buffer[i] = (char *)calloc(1, sizeof(char)*write_width);

    box(command_window, 0, 0);
    box(info_window, 0, 0);

    //add all commands here
    mvwprintw(command_window, 1, 1, "F1 - Exit");

    wrefresh(command_window);
    wrefresh(info_window);
}

void close_ui() {
    for (int i = 0;i < write_height; ++i)
        free(mega_buffer[i]);
    free(mega_buffer);
    //for the love of god dont break the whole terminal if it worked as expected
    delwin(info_window);
    delwin(command_window);
    endwin();
}

int lines_pos = 0;
int total_lines = 0;
void add_msg(const char * restrict msg) {
    ++total_lines;
    //copy in the line
    strcpy(mega_buffer[lines_pos++], msg);
    if (lines_pos >= write_height) {
        lines_pos = 0;
    }

    //clear the output
    for (int i = 0;i < write_height; ++i) {
        mvwhline(info_window, i + 1, 1, ' ', write_width);
    }

    int j = 0;
    if (total_lines > lines_pos) {
        for (int i = lines_pos + 1; i < write_height; ++i) {
            mvwprintw(info_window, j++ + 1, 1, mega_buffer[i]);
        }
    }
    for (int i = 0; i < lines_pos; ++i) {
        mvwprintw(info_window, j++ + 1, 1, mega_buffer[i]);
    }

    wrefresh(info_window);
}
