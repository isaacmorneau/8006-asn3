#ifndef IPTABLES_H
#define IPTABLES_H
/*
 * Author & Designer: John Agapeyev
 * Modified by: Isaac Morneau
 * Date: 2018-03-05
 * Notes: The functions for blocking and unblocking ips in netfilter
 * Revision: 2018-03-05
 *      removed restrict
 * */
void block_ip(const char * ip);
void unblock_ip(const char * ip);

#endif
