//
//  TCPSocket.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/30/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#include "tcpserversocket.h"
using namespace std;

TCPServerSocket::TCPServerSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Stream Socket
    bzero(&info, sizeof(info));
}

/**
 * Bind socket
 * @param address address to bind
 * @param port port to bind
 * @param qlim queue limit
 */
void TCPServerSocket::bindAndListen(const char *address, int port, int qlim) {
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(address);
    info.sin_port = htons(port);
    bind(sockfd, (struct sockaddr *)&info, sizeof(info));
    listen(sockfd, qlim);
}

/**
 * Bind socket
 * @param address address to bind
 * @param port port to bind
 */
void TCPServerSocket::bindAndListen(const char *address, int port) {
    bindAndListen(address, port, MAX_QUEUE_LIMIT);
}

/**
 * Get socket file descriptor
 * @return socket file descriptor
 */
int TCPServerSocket::getFD() {
    return sockfd;
}

/**
 * Accept a connection and return child socket instance
 * @return child socket instance
 */
TCPChildSocket* TCPServerSocket::acceptConnection() {
    addrlen = sizeof(clientInfo);
    int clientSockfd = accept(sockfd, (struct sockaddr*) &clientInfo, &addrlen);
    return new TCPChildSocket(clientSockfd, clientInfo);
}
