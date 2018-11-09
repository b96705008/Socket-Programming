//
//  LinkDataset.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef linkdataset_h
#define linkdataset_h

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "linkdata.h"
#include "dataparser.h"
using namespace std;
#endif /* LinkDataset_hpp */

class LinkDataset {
public:
//    static string delimeter;
//    static vector<string> splitCSVLine(string);
    
    LinkDataset(string);
    
    bool containsID(int);
    LinkData get(int);

private:
    void loadData(ifstream &);
    unordered_map<int, LinkData> dataMap;
};
