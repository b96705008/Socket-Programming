//
//  DataParser.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef dataparser_h
#define dataparser_h

#define NOT_FOUND "NOT_FOUND"
#define BAD_REQUEST "BAD_REQUEST"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <iostream>
#include <vector>
#endif /* DataParser_hpp */

/**
 * Used to process string data
 */
class DataParser {
public:
    static std::string delimeter; // delimeter to split field in string
    static std::vector<std::string> splitCSVLine(std::string); // split csv like string to fields
};
