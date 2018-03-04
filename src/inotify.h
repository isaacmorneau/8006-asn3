#ifndef INOTIFY_H
#define INOTIFY_H

int create_inotify_descriptor(void);
void wait_for_logs(const int inot_fd, const int fail_max, const int timeout);
void process_secure_logs(const int fail_max, const int timeout);

#endif
