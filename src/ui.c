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

const char * title = "8006-asn3: Isaac & John; Splurple";

void init_ui() {
    //start up ncurses and setup key handling
    //honestly why are there so many different init functions???
    initscr();
    start_color();
    use_default_colors();
    raw();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    NCURSES_BULLSHIT_INIT;

    write_width = COLS - COMMAND_WIDTH - 2;
    write_height = LINES - 2;

    command_window = newwin(LINES-1, COMMAND_WIDTH, 1, 0);
    info_window = newwin(LINES-1, write_width, 1, COMMAND_WIDTH + 1);

    //allocate a grid for the output buffer
    mega_buffer = (char **)calloc(1, sizeof(char*)*write_height);
    for (int i = 0;i < write_height; ++i)
        mega_buffer[i] = (char *)calloc(1, sizeof(char)*write_width);

    //draw window boxes
    box(command_window, 0, 0);
    box(info_window, 0, 0);

    //start up the colirs
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_BLUE, -1);
    init_pair(4, COLOR_MAGENTA, -1);

    //set the title
    wattron(stdscr, COLOR_PAIR(3));
    mvwhline(stdscr, 0, 0, '-', COLS);
    wattroff(stdscr, COLOR_PAIR(3));
    wattron(stdscr, COLOR_PAIR(4));
    mvwprintw(stdscr, 0, (COLS/2)-(strlen(title)/2), title);
    wattroff(stdscr, COLOR_PAIR(4));


    //add all commands here
    wattron(command_window, COLOR_PAIR(1));
    mvwprintw(command_window, 1, 1, "F1 - Exit");
    mvwprintw(command_window, 2, 1, "F2 - Start");
    mvwprintw(command_window, 3, 1, "F3 - Set Attempts");
    mvwprintw(command_window, 4, 1, "F4 - Set Timelimit");
    wattroff(command_window, COLOR_PAIR(1));

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
    strncpy(mega_buffer[lines_pos++], msg, write_width);
    if (lines_pos >= write_height) {
        lines_pos = 0;
    }

    //clear the output
    for (int i = 1; i < write_height; ++i) {
        mvwhline(info_window, i, 1, ' ', write_width - 2);
    }

    wattron(info_window, COLOR_PAIR(2));
    int j = 1;
    if (total_lines > lines_pos) {
        for (int i = lines_pos + 1; i < write_height; ++i) {
            mvwprintw(info_window, j++, 1, mega_buffer[i]);
        }
    }
    for (int i = 0; i < lines_pos; ++i) {
        mvwprintw(info_window, j++, 1, mega_buffer[i]);
    }
    wattroff(info_window, COLOR_PAIR(2));

    wrefresh(info_window);
}

void get_msg(char * restrict msg, int len) {
    wattron(info_window, COLOR_PAIR(2));
    nocbreak();
    echo();
    mvwgetnstr(info_window, lines_pos + 1, 1, msg, len);
    wattroff(info_window, COLOR_PAIR(2));
    add_msg(msg);
    noecho();
    cbreak();
}
