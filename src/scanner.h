#ifndef SCANNER_H
#define SCANNER_H

#include <netinet/in.h>
int scanPort(struct sockaddr_in target_addr, int target_port);

#endif