#ifndef IPTABLES_H
#define IPTABLES_H

void block_ip(const char *restrict ip);
void unblock_ip(const char *restrict ip);

#endif
