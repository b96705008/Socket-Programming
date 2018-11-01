//
//  DataParser.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#include "DataParser.hpp"
using namespace std;

string DataParser::delimeter = ",";

vector<string> DataParser::splitCSVLine(string line) {
    vector<string> tokens;
    string token;
    size_t pos = 0;
    
    while ((pos = line.find(delimeter)) != string::npos) {
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + delimeter.length());
    }
    
    if (strlen(line.c_str()) > 0) {
        tokens.push_back(line);
    }
    
    return tokens;
}
