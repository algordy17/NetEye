#ifndef THREADS_H
#define THREADS_H

#include <netinet/in.h>

void startScan(struct sockaddr_in target_addr, int start_port, int end_port);

#endif