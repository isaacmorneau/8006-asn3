#ifndef INOTIFY_H
#define INOTIFY_H
/*
 * Author & Designer: John Agapeyev
 * Modified by: Isaac Morneau
 * Date: 2018-03-05
 * Notes: The functions for monitoring and handling the log files
 * */
int create_inotify_descriptor(void);
void wait_for_logs(const int inot_fd, const int fail_max, const int timeout, const int daemon);
void process_secure_logs(const int fail_max, const int timeout, const int daemon);

#endif
