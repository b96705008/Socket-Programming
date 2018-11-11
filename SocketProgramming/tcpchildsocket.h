//
//  TCPChildSocket.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/31/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef tcpchildsocket_h
#define tcpchildsocket_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include "defs.h"
#endif /* TCPChildSocket_hpp */

/**
 * Encapsulate TCP child socket
 */
class TCPChildSocket {
public:
    TCPChildSocket(int, struct sockaddr_in);
    ~TCPChildSocket();
    
    int getFD();
    std::string getDataString();
    bool recvData();
    bool sendData(std::string);
    int getClientPort();
    
private:
    int sockfd;
    struct sockaddr_in clientInfo;
    ssize_t numbytes;
    char buf[MAXBUFLEN];
};
