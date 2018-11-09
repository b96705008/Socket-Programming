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

TCPChildSocket::~TCPChildSocket() {
    close(sockfd);
}

int TCPChildSocket::getFD() {
    return sockfd;
}

bool TCPChildSocket::recvData() {
    numbytes = recv(sockfd, buf, MAXBUFLEN-1, 0);
    if (numbytes == -1) {
        perror("recv");
        return false;
    }
    
    buf[numbytes] = '\0';
    return true;
}

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

string TCPChildSocket::getDataString() {
    string rawStr(buf);
    return rawStr;
}

int TCPChildSocket::getClientPort() {
    return ntohs(clientInfo.sin_port);
}


