//
//  UDPSocket.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/28/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//
#include "UDPSocket.hpp"
using namespace std;


UDPSocket::UDPSocket() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&info, sizeof(info));
}

void UDPSocket::bindSocket(const char * address, int port) {
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(address);
    info.sin_port = htons(port);
    bind(sockfd, (struct sockaddr *)&info, sizeof(info));
}

bool UDPSocket::recvData(struct sockaddr_in &their_addr) {
    socklen_t addr_len = sizeof(their_addr);
    numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0,
                        (struct sockaddr *)&their_addr, &addr_len);
    
    if (numbytes == -1) {
        perror("recvfrom");
        return false;
    }
    
    buf[numbytes] = '\0';
    return true;
}

string UDPSocket::getDataString() {
    string rawStr(buf);
    return rawStr;
}

int UDPSocket::getFD() {
    return sockfd;
}

bool UDPSocket::sendData(struct sockaddr_in &their_addr, string data) {
    char *inputBuf = new char[data.length()+1];
    strcpy(inputBuf, data.c_str());
    socklen_t addr_len = sizeof(their_addr);
    numbytes = sendto(sockfd, inputBuf, strlen(inputBuf), 0,
                       (struct sockaddr *)&their_addr, addr_len);

    if (numbytes == -1) {
        perror("sendto");
        return false;
    }
    
    delete [] inputBuf;

    return true;
}



