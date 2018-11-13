//
//  LinkDataset.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//
#include "linkdataset.h"
using namespace std;

LinkDataset::LinkDataset(string filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Can't load or found file: " + filename << endl;
        exit(1);
    }
    loadData(fin);
}

/**
 * Load data from file
 * @param fin file input stream
 */
void LinkDataset::loadData(ifstream &fin) {
    string line = "";
    while (getline(fin, line)) {
        vector<string> tokens = DataParser::splitCSVLine(line);
        LinkData data(&tokens);
        dataMap.insert(make_pair(data.id(), data));
    }
}

/**
 * Check if contains specific link id
 * @return if contains
 */
bool LinkDataset::containsID(int linkID) {
    return dataMap.find(linkID) != dataMap.end();
}

/**
 * Search link data and return
 * @return link data
 */
LinkData LinkDataset::get(int linkID) {
    return dataMap.find(linkID)->second;
}




