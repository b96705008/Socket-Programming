//
//  serverB.cpp
//  SocketProgramming
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
#include "udpsocket.h"
#include "linkdataset.h"
#include "defs.h"
using namespace std;


int main(int argc, const char* argv[]) {
    // init dataset
    struct sockaddr_in clientInfo;
    LinkDataset dataset(DATABASE_B);
    
    // create and bind socket
    UDPSocket server;
    if (server.getFD() == -1) {
        exit(1);
    }
    server.bindSocket(LOCAL_ADDR, SERVER_B_UDP_PORT);
    
    printf("The Server B is up and running using UDP on port <%d>.\n", SERVER_B_UDP_PORT);
    
    while (true) {
        // receive data
        bool isSuccess = server.recvData(clientInfo);
        
        if (!isSuccess) {
            server.sendData(clientInfo, BAD_REQUEST);
        } else {
            // get request link id
            string dataStr = server.getDataString();
            int requestID = stoi(dataStr);
            printf("The Server B received input <%d>\n", requestID);
            
            // search link profile for link id
            if (dataset.containsID(requestID)) {
                // respond link data profile
                LinkData data = dataset.get(requestID);
                printf("The server B has found <1> match\n");
                server.sendData(clientInfo, data.getDataString());
            } else {
                // not found
                printf("The server B has found <0> match\n");
                server.sendData(clientInfo, NOT_FOUND);
            }
            printf("The Server B finished sending the output to AWS\n");
        }
    }
    
    return 0;
}

