//
//  main.cpp
//  BackendA
//
//  Created by Tai-Yi Kuo on 10/29/18.
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
#include "UDPSocket.hpp"
#include "LinkDataset.hpp"
#include "defs.h"
using namespace std;


int main(int argc, const char * argv[]) {
    // init dataset
    struct sockaddr_in clientInfo;
    LinkDataset dataset(DATABASE_A);
    
    // create socket
    UDPSocket server;
    if (server.getFD() == -1) {
        exit(1);
    }
    server.bindSocket(LOCAL_ADDR, SERVER_A_UDP_PORT);
    
    // recv data
    printf("The Server A is up and running using UDP on port <%d>.\n", SERVER_A_UDP_PORT);
    
    while (true) {
        bool isSuccess = server.recvData(clientInfo);
        
        if (!isSuccess) {
            server.sendData(clientInfo, BAD_REQUEST);
        } else {
            string dataStr = server.getDataString();
            int requestID = stoi(dataStr);
            printf("The Server A received input <%d>\n", requestID);
            
            if (dataset.containsID(requestID)) {
                LinkData data = dataset.get(requestID);
                printf("The server A has found <1> match\n");
                server.sendData(clientInfo, data.getDataString());
            } else {
                printf("The server A has found <0> match\n");
                server.sendData(clientInfo, NOT_FOUND);
            }
            printf("The Server A finished sending the output to AWS\n");
        }
    }
    
    return 0;
}
