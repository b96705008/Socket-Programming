//
//  UDPSocket.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/28/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//
#include "udpsocket.h"
using namespace std;


UDPSocket::UDPSocket() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Datagram Socket
    bzero(&info, sizeof(info));
}

/**
 * Bind socket
 * @param address address to bind
 * @param port port to bind
 * @return error code
 */
int UDPSocket::bindSocket(const char * address, int port) {
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(address);
    info.sin_port = htons(port);

    // refer from beej.us. reuse socket number when restart
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    return bind(sockfd, (struct sockaddr *)&info, sizeof(info));
}

/**
 * Receive data
 * @param their_addr used to store sender's address infomation
 * @return if successfully receive data
 */
bool UDPSocket::recvData(struct sockaddr_in &their_addr) {
    socklen_t addr_len = sizeof(their_addr);
    numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0,
                        (struct sockaddr *)&their_addr, &addr_len);
    
    if (numbytes == -1) {
        //perror("recvfrom");
        return false;
    }
    
    buf[numbytes] = '\0';
    return true;
}

/**
 * Get current received data string
 * @return data string
 */
string UDPSocket::getDataString() {
    string rawStr(buf);
    return rawStr;
}

/**
 * Get socket file descriptor
 * @return socket file descriptor
 */
int UDPSocket::getFD() {
    return sockfd;
}

/**
 * Send data to specific address
 * @param their_addr receiver's address
 * @param data data to send
 * @return if successfully send data
 */
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



