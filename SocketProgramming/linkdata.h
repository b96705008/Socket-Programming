//
//  LinkData.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/28/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef linkdata_h
#define linkdata_h

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#endif /* LinkData_hpp */

/**
 * Represent a link data
 */
class LinkData {
public:
    LinkData();
    LinkData(vector<string>*);
    
    int id(); // get link id
    void setProperties(vector<string>*); // set properties from vector
    string getDataString(); // get data string from profile
    
protected:
    int linkID;
    float bandwidth;
    float lengthKM;
    float velocity;
    float noisePower;
};
