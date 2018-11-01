//
//  client.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/31/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include "defs.h"
using namespace std;


int main(int argc, char *argv[]) {
    // check argument
    if (argc < 4) {
        cerr << "number of argument should be 3" << endl;
        exit(1);
    }
    string query = string(argv[1]) + ","
        + string(argv[2]) + ","
        + string(argv[3]);
    
    // create socket
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd == -1) {
        printf("Fail to create a socket.");
        exit(1);
    }
    
    // aws server connection
    struct sockaddr_in awsInfo;
    bzero(&awsInfo, sizeof(awsInfo));
    awsInfo.sin_family = PF_INET;
    awsInfo.sin_addr.s_addr = inet_addr(LOCAL_ADDR);
    awsInfo.sin_port = htons(AWS_CLIENT_TCP_PORT);
    
    // connect server
    int err = connect(sockfd, (struct sockaddr *)&awsInfo, sizeof(awsInfo));
    if (err == -1) {
        printf("AWS Connection error");
    }
    cout << "The client is up and running." << endl;
    
    // send message to server
    ssize_t numbytes;
    char *sendMessage = new char[query.length()+1];
    strcpy(sendMessage, query.c_str());
    char receiveMessage[MAXBUFLEN] = {};
    
    send(sockfd, sendMessage, strlen(sendMessage), 0);
    delete [] sendMessage;
    printf("The client sent link ID=<%s>, size=<%s>, and power=<%s> to AWS\n",
           argv[1], argv[2], argv[3]);
    
    numbytes = recv(sockfd, receiveMessage, MAXBUFLEN-1, 0);
    receiveMessage[numbytes] = '\0';
    string resp = string(receiveMessage);
    
    if (resp == NOT_FOUND) {
        printf("Found no matches for link <%s>\n", argv[1]);
    } else {
        printf("The delay for link <%s> is <%s>ms\n", argv[1], receiveMessage);
    }
    
    // close connection
    close(sockfd);
    return 0;
}
