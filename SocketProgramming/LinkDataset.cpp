//
//  LinkDataset.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "LinkDataset.hpp"
#include "DataParser.hpp"
using namespace std;

LinkDataset::LinkDataset(string filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "can't load file" << endl;
        exit(1);
    }
    loadData(fin);
}

void LinkDataset::loadData(ifstream &fin) {
    string line = "";
    while (getline(fin, line)) {
        vector<string> tokens = DataParser::splitCSVLine(line);
        LinkData data(&tokens);
        dataMap.insert(make_pair(data.id(), data));
    }
}

bool LinkDataset::containsID(int linkID) {
    return dataMap.find(linkID) != dataMap.end();
}

LinkData LinkDataset::get(int linkID) {
    return dataMap.find(linkID)->second;
}




