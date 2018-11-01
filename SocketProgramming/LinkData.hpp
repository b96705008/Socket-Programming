//
//  LinkData.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/28/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef LinkData_hpp
#define LinkData_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#endif /* LinkData_hpp */

class LinkData {
public:
    LinkData();
    LinkData(vector<string>*);
    
    int id();
    void setProperties(vector<string>*);
    string getDataString();
    
protected:
    int linkID;
    float bandwidth;
    float lengthKM;
    float velocity;
    float noisePower;
};
