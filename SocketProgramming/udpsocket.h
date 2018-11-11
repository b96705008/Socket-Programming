//
//  UDPSocket.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef udpsocket_h
#define udpsocket_h

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
#endif /* udpsocket_h */

/**
 * Encapsulate UDP socket funcions
 */
class UDPSocket {
public:
    UDPSocket();
    int bindSocket(const char *, int);
    int getFD();
    std::string getDataString();
    bool recvData(struct sockaddr_in&);
    bool sendData(struct sockaddr_in&, std::string);
    
private:
    int sockfd;
    struct sockaddr_in info;
    ssize_t numbytes;
    char buf[MAXBUFLEN];
};
