//
//  TCPChildSocket.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/31/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#include "tcpchildsocket.h"
using namespace std;

TCPChildSocket::TCPChildSocket(int clientSockfd, struct sockaddr_in their_addr) {
    sockfd = clientSockfd;
    clientInfo = their_addr;
}

/**
 * Close socket when being destroyed
 */
TCPChildSocket::~TCPChildSocket() {
    close(sockfd);
    bzero(&buf, sizeof(buf));
    bzero(&clientInfo, sizeof(clientInfo));
}

/**
 * Get socket file descriptor
 * @return socket file descriptor
 */
int TCPChildSocket::getFD() {
    return sockfd;
}

/**
 * Receive data from client
 * @return if successfully receive data
 */
bool TCPChildSocket::recvData() {
    numbytes = recv(sockfd, buf, MAXBUFLEN-1, 0);
    if (numbytes == -1) {
        perror("recv");
        return false;
    }
    
    buf[numbytes] = '\0';
    return true;
}

/**
 * Send data to the client
 * @param data data to send
 * @return if successfully send data
 */
bool TCPChildSocket::sendData(string data) {
    char *inputBuf = new char[data.length()+1];
    strcpy(inputBuf, data.c_str());
    numbytes = send(sockfd, inputBuf, strlen(inputBuf), 0);
    if (numbytes == -1) {
        perror("send");
        return false;
    }
    
    delete [] inputBuf;
    
    return true;
}

/**
 * Get current received data string
 * @return data string
 */
string TCPChildSocket::getDataString() {
    string rawStr(buf);
    return rawStr;
}

/**
 * Get client's port number
 * @return port number in int type
 */
int TCPChildSocket::getClientPort() {
    return ntohs(clientInfo.sin_port);
}


