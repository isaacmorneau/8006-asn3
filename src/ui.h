#ifndef UI_H
#define UI_H
/*
 * Author & Designer: Isaac Morneau
 * Date: 2018-03-05
 * Notes: functions for handling IO via ncurses
 * */

void init_ui(void);
void close_ui(void);
void add_msg(const char * msg);
void get_msg(char * msg, const int len);

#endif
