//
//  defs.h
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef defs_h
#define defs_h

// localhost
#define LOCAL_ADDR "127.0.0.1"

// response message
#define NOT_FOUND "NOT_FOUND"
#define BAD_REQUEST "BAD_REQUEST"
#define CLIENT_INPUT "CLIENT_INPUT"
#define DELAY_RESULT "DELAY_RESULT"

// database
#define DATABASE_A "database_a.csv"
#define DATABASE_B "database_b.csv"

// port
#define SERVER_A_UDP_PORT 21162
#define SERVER_B_UDP_PORT 22162
#define SERVER_C_UDP_PORT 23162
#define AWS_UDP_PORT 24162
#define AWS_CLIENT_TCP_PORT 25162
#define AWS_MONITOR_TCP_PORT 26162

// other
#define MAXBUFLEN 256
#define MAX_QUEUE_LIMIT 5

#endif /* defs_h */
