//
//  TCPSocket.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/30/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef TCPSocket_hpp
#define TCPSocket_hpp

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <vector>
#include "TCPChildSocket.hpp"
#include "defs.h"
using namespace std;

#endif /* TCPSocket_hpp */

class TCPServerSocket {
public:
    TCPServerSocket();
    void bindAndListen(const char *, int);
    void bindAndListen(const char *, int, int);
    TCPChildSocket* acceptConnection();
    int getFD();

private:
    int sockfd;
    struct sockaddr_in info;
    struct sockaddr_in clientInfo;
    socklen_t addrlen;
};
