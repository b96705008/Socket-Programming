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
 * @return error code
 */
int TCPServerSocket::bindSocket(const char *address, int port) {
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(address);
    info.sin_port = htons(port);
    return bind(sockfd, (struct sockaddr *)&info, sizeof(info));
}

/**
 * Start to listen for connection
 * @return error code
 */
int TCPServerSocket::listenSocket() {
    return listen(sockfd, MAX_QUEUE_LIMIT);
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

/**
 * Close the parent socket
 */
void TCPServerSocket::closeSocket() {
    close(sockfd);
}