//
//  TCPSocket.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/30/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#include "TCPServerSocket.hpp"
using namespace std;

TCPServerSocket::TCPServerSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&info, sizeof(info));
}

void TCPServerSocket::bindAndListen(const char *address, int port, int qlim) {
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(address);
    info.sin_port = htons(port);
    bind(sockfd, (struct sockaddr *)&info, sizeof(info));
    listen(sockfd, qlim);
}

void TCPServerSocket::bindAndListen(const char *address, int port) {
    bindAndListen(address, port, MAX_QUEUE_LIMIT);
}

int TCPServerSocket::getFD() {
    return sockfd;
}

TCPChildSocket* TCPServerSocket::acceptConnection() {
    addrlen = sizeof(clientInfo);
    int clientSockfd = accept(sockfd, (struct sockaddr*) &clientInfo, &addrlen);
    return new TCPChildSocket(clientSockfd, clientInfo);
}
