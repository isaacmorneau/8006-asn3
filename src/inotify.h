#ifndef INOTIFY_H
#define INOTIFY_H

int create_inotify_descriptor(void);
void wait_for_logs(const int inot_fd);
void process_secure_logs(void);

#endif
