//
//  TCPSocket.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/30/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef tcpserversocket_h
#define tcpserversocket_h

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
#include "tcpchildsocket.h"
#include "defs.h"
#endif /* TCPSocket_hpp */

/**
 * Encapsulate TCP parent socket
 */
class TCPServerSocket {
public:
    TCPServerSocket();
    int bindSocket(const char *, int);
    int listenSocket();
    // bool bindAndListen(const char *, int);
    // bool bindAndListen(const char *, int, int);
    TCPChildSocket* acceptConnection();
    int getFD();

private:
    int sockfd;
    struct sockaddr_in info;
    struct sockaddr_in clientInfo;
    socklen_t addrlen;
};
