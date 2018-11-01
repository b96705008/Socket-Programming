//
//  serverC.cpp
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
#include "UDPSocket.hpp"
#include "ComputedLinkData.hpp"
#include "DataParser.hpp"
#include "defs.h"
using namespace std;

int main() {
    // init variable
    struct sockaddr_in clientInfo;

    // create socket
    UDPSocket server;
    if (server.getFD() == -1) {
        exit(1);
    }
    server.bindSocket(LOCAL_ADDR, SERVER_C_UDP_PORT);
    
    // recv data
    printf("The Server C is up and running using UDP on port <%d>.\n", SERVER_C_UDP_PORT);
    
    while (true) {
        bool isSuccess = server.recvData(clientInfo);
        
        if (!isSuccess) {
            server.sendData(clientInfo, BAD_REQUEST);
            continue;
        }
        // parse data
        string dataStr = server.getDataString();
        vector<string> tokens = DataParser::splitCSVLine(dataStr);
        ComputedLinkData data(&tokens);
        printf("The Server C received link information of link <%d>, file size <%f>, and signal power <%f>\n", data.id(), data.fileSize(), data.power());
        
        // compute
        data.compute();
        printf("The server C finished the calculation for link <%d>\n", data.id());
        
        // response
        server.sendData(clientInfo, data.getDelayString());
        cout << "The Server C finished sending the output to AWS" << endl;
    }
}



