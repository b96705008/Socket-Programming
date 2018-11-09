//
//  main.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/28/18.
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
#include "linkdata.h"
#include "udpsocket.h"
#include "tcpserversocket.h"
#include "dataparser.h"
#include "defs.h"
using namespace std;


struct sockaddr_in getServerAddr(int);
void testRequestLink(string, UDPSocket&, struct sockaddr_in&);
bool queryLinkDataFromServer(string, string, UDPSocket&, struct sockaddr_in&, LinkData&);
bool queryLinkData(string, UDPSocket&, struct sockaddr_in&, struct sockaddr_in&, LinkData&);
string requestForComputing(LinkData&, string, string, UDPSocket&, struct sockaddr_in&);

int main(int argc, const char *argv[]) {
    // Boot Up
    cout << "The AWS is up and running." << endl;
    
    // Get backend info
    struct sockaddr_in backendA = getServerAddr(SERVER_A_UDP_PORT);
    struct sockaddr_in backendB = getServerAddr(SERVER_B_UDP_PORT);
    struct sockaddr_in backendC = getServerAddr(SERVER_C_UDP_PORT);
    
    // Create UDP client
    UDPSocket queryClient;
    if (queryClient.getFD() == -1) {
        exit(1);
    }
    queryClient.bindSocket(LOCAL_ADDR, AWS_UDP_PORT);
    
    // create TCP server for monitor and wait for connection
    TCPServerSocket logServer;
    if (logServer.getFD() == -1) {
        exit(1);
    }
    logServer.bindAndListen(LOCAL_ADDR, AWS_MONITOR_TCP_PORT);
    TCPChildSocket *monitorSocket = logServer.acceptConnection();
    int monitorPort = monitorSocket->getClientPort();
    
    // Create TCP server for client
    TCPServerSocket forwardServer;
    if (forwardServer.getFD() == -1) {
        exit(1);
    }
    forwardServer.bindAndListen(LOCAL_ADDR, AWS_CLIENT_TCP_PORT);
    
    while (true) {
        TCPChildSocket *childSocket = forwardServer.acceptConnection();
        childSocket->recvData();
        string clientInput = childSocket->getDataString();
        vector<string> tokens = DataParser::splitCSVLine(clientInput);
        
        if (tokens.size() < 3) {
            childSocket->sendData(BAD_REQUEST);
        } else {
            int clientPort = childSocket->getClientPort();
            string requestLinkID = tokens[0];
            string fileSize = tokens[1];
            string signalPower = tokens[2];
            
            printf("The AWS received link ID=<%s>, size=<%s>, and power=<%s> from the client using TCP over port <%d>\n", requestLinkID.c_str(), fileSize.c_str(), signalPower.c_str(), clientPort);
            
            // log client input
            monitorSocket->sendData(string(CLIENT_INPUT) + "," + clientInput);
            printf("The AWS sent link ID=<%s>, size=<%s>, and power=<%s> to the monitor using TCP over port <%d>\n", requestLinkID.c_str(), fileSize.c_str(), signalPower.c_str(), monitorPort);
            
            LinkData data;
            bool found = queryLinkData(requestLinkID, queryClient, backendA, backendB, data);
            if (found) {
                string resp = requestForComputing(data, fileSize, signalPower, queryClient, backendC);
                vector<string> delays = DataParser::splitCSVLine(resp);
                childSocket->sendData(delays[2]);
                printf("The AWS sent delay=<%s>ms to the client using TCP over port <%d>\n", delays[2].c_str(), clientPort);
                
                // log computed result
                monitorSocket->sendData(string(DELAY_RESULT) + "," + requestLinkID + "," + resp);
                printf("The AWS sent detailed results to the monitor using TCP over port <%d>\n", monitorPort);
                
            } else {
                childSocket->sendData(NOT_FOUND);
                
                // log not found
                monitorSocket->sendData(string(NOT_FOUND) + "," + requestLinkID);
                
                printf("The AWS sent No Match to the monitor and the client using TCP over ports <%d> and <%d>, respectively\n", monitorPort, clientPort);
            }
        }
        delete childSocket;
    }
    
    return 0;
}

struct sockaddr_in getServerAddr(int port) {
    struct sockaddr_in info;
    bzero(&info, sizeof(info));
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(LOCAL_ADDR);
    info.sin_port = htons(port);
    return info;
}

string requestForComputing(LinkData &data, string fileSize, string signalPower,
                         UDPSocket &client, struct sockaddr_in &serverC) {
    string dataToComputed = data.getDataString() + "," + fileSize + "," + signalPower;
    
    client.sendData(serverC, dataToComputed);
    printf("The AWS sent link ID=<%d>, size=<%s>, power=<%s>, and link information to Backend-Server C using UDP over port <%d>\n", data.id(), fileSize.c_str(), signalPower.c_str(), ntohs(serverC.sin_port));
    
    client.recvData(serverC);
    string resp = client.getDataString();
    printf("The AWS received outputs from Backend-Server C using UDP over port <%d>\n", ntohs(serverC.sin_port));
    return resp;
}

bool queryLinkData(string id, UDPSocket &client,
                     struct sockaddr_in &serverA, struct sockaddr_in &serverB,
                     LinkData &data) {
    bool found = false;
    int matchA = 0;
    int matchB = 0;

    if (queryLinkDataFromServer(id, "A", client, serverA, data)) {
        matchA = 1;
        found = true;
    }
    printf("The AWS received <%d> matches from Backend-Server <%s> using UDP over port <%d>\n", matchA, "A", ntohs(serverA.sin_port));
    
    
    if (queryLinkDataFromServer(id, "B", client, serverB, data)) {
        matchB = 1;
        found = true;
    }
    printf("The AWS received <%d> matches from Backend-Server <%s> using UDP over port <%d>\n", matchB, "B", ntohs(serverB.sin_port));
    
    return found;
}

bool queryLinkDataFromServer(string id, string name, UDPSocket &client, struct sockaddr_in &serverInfo, LinkData &data) {
    bool isSuccess = client.sendData(serverInfo, id);
    printf("The AWS sent link ID=<%s> to Backend-Server <%s> using UDP over port <%d>\n", id.c_str(), name.c_str(), ntohs(serverInfo.sin_port));
    
    if (!isSuccess) {
        return false;
    }
    
    isSuccess = client.recvData(serverInfo);
    if (!isSuccess) {
        return false;
    }
    
    string resp = client.getDataString();
    if (resp == NOT_FOUND) {
        return false;
    }
    
    vector<string> tokens = DataParser::splitCSVLine(client.getDataString());
    data.setProperties(&tokens);
    return true;
}
