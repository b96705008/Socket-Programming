# Socket Programming

## Summary
In this project, my goal is to create a service which can respond the end-to-end delay for client given link request. I follow the architecture requirements and developed 4 servers, 1 monitor, and 1 client program. They serve different roles. We will discuss details on "Socket Programs" section.

## Socket Programs
1. serverA and serverB:
They read link data from files and run as UDP server. They provide the service of searching for link profile. Each of they keep part of data, so aws would request both of them for the any query from client. PS: Please put the database files on the same path as serverA and serverB.

2. serverC:
Once receiving request for computing for given link profile, file size, and signal power, it would compute transmission delay, propagation delay, and end-to-end delay then respond. The unit of delay would be million second. It runs un UDP service.

3. aws:
It is the core of the server architecture. It would receive the delay query from client, then query the link profile data from serverA and serverB, request for computing from serverC, log message to monitor, and respond end-to-end delay to client. When it communicate with server A, B, C, it acts as UDP client. It also creates 2 TCP sockets that wait for the connection from monitor and client. However, it only accept one monitor. After accepting monitor, it would go to serve for multiple queries sent from clients.

4. monitor:
When aws receives client's request and computing result, it would forward message to monitor. Monitor would get the detail of delay messages, including transmission delay, propagation delay, and end-to-end delay, then print the information. The architecture of monitor is different from client. It runs TCP client that would connect to aws when boot up and print for every message received from aws. Therefore, monitor should start after the boot up of aws server.
There is a important thing, I make monitor to close socket and stop once aws is shutdown, because I think this would make monitor to close socket elegantly.

5. client:
This is the program which can send link id, file size, and signal power given by user, and expect to get delay result from aws. If link id doesn't exist in serverA and serverB's storage, then aws would respond with "NOT_FOUND" message. It runs a TCP client when boot up, and it can be used repeatedly. Once it get the response and print result, then it would close and stop.

## Structure
In order to prevent me from repeatedly writing same code, I used Object-Oriented design on this project. This would also make the whole project architecture more clear. So I used many files that contains class that encapsulate repeated logic and can be used by other main program. Below are the introduction of these files:

* defs.h
This is a conifg file. I define static port, server IP, response message, and database file names. It would be used by many of other servers and client programs.

* dataparser.h, dataparser.cpp
This is a utilities tool, which process message to/from string, buffer, and vector format.

* linkdata.h, linkdata.cpp
This file contains the class: LinkData, which represent and store each link profile data. It would be used by serverA and serverB.

* computedlinkdata.h, computedlinkdata.cpp
This file contains the class: ComputedLinkData, which inherents from LinkData, and extend it with packet size and signal power. The class implements many delay computation methods, which would be used by serverC.

* udpsocket.h, udpsocket.cpp
Writing UDP sockets repeatedly would not be a good idea. We will use it in many programs, including serverA, serverB, serverC, and aws. Therefore, I encapsulate the UDP socket functions into the UDPSocket class. With UDPSocket class, we can easily create a UDP socket by only given port and address.

* tcpserversocket.h, tcpserversocket.cpp, tcpchildsocket.h, tcpchildsocket.cpp
It is also a good idea to encapsulate TCP socket funcions. However, TCP socket is more complicated that it can generate child sockets, which serves different roles from parent socket. Therefore, I design two different tcp socket class for them to use, TCPServerSocket is for parent socket and it would generate TCPChildSocket instance. This would be used by aws server.

* serverA.cpp, serverB.cpp, serverC.cpp, aws.cpp, monitor.cpp, client.cpp
They are mains socket programs and serve the role as the architecture requirements. 

## References
1. http://www.beej.us/guide/bgnet (mainly reference)
2. http://zake7749.github.io/2015/03/17/SocketProgramming (socket lib explanation)
3. https://www.sczyh30.com/posts/C-C/cpp-stl-hashmap (hash map)

## How to Run
```
make clean // It is used for cleaning all compiled outputs
make all // compile all files and creates executables
make serverA // Please put both the database_a.csv and database_b.csv on the same path as serverA and serverB
make serverB
make serverC
make aws
make monitor
./client <LINK_ID> <SIZE> <POWER> // can be executed repeatedly
```


