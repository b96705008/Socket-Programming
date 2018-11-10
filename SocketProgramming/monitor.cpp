//
//  monitor.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 11/1/18.
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
#include "dataparser.h"
#include "defs.h"
using namespace std;

int main(int argc, char *argv[]) {
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
    awsInfo.sin_port = htons(AWS_MONITOR_TCP_PORT);
    
    // connect server
    int err = connect(sockfd, (struct sockaddr *)&awsInfo, sizeof(awsInfo));
    if (err == -1) {
        printf("AWS Connection error");
    }
    cout << "The monitor is up and running." << endl;
    
    // wait and log messages
    ssize_t numbytes;
    char message[MAXBUFLEN];
    while (true) {
        // get and parse message
        numbytes = recv(sockfd, message, MAXBUFLEN-1, 0);
        message[numbytes] = '\0';
        vector<string> tokens = DataParser::splitCSVLine(message);
        
        // check and log message
        string messageType = tokens[0];
        if (messageType == CLIENT_INPUT) {
            printf("The monitor received link ID=<%s>, size=<%s>, and power=<%s> from the AWS\n", tokens[1].c_str(), tokens[2].c_str(), tokens[3].c_str());
        } else if (messageType == DELAY_RESULT) {
            printf("The result for link <%s>: Tt = <%s>ms, Tp = <%s>ms, Delay = <%s>ms\n", tokens[1].c_str(), tokens[2].c_str(), tokens[3].c_str(), tokens[4].c_str());
        } else if (messageType == NOT_FOUND){
            printf("Found no matches for link <%s>\n", tokens[1].c_str());
        }
    }
    
    //close(sockfd);
    return 0;
}







