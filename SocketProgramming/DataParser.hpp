//
//  DataParser.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef DataParser_hpp
#define DataParser_hpp

#define NOT_FOUND "NOT_FOUND"
#define BAD_REQUEST "BAD_REQUEST"

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#endif /* DataParser_hpp */

class DataParser {
public:
    static string delimeter;
    static vector<string> splitCSVLine(string);
};
