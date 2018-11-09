//
//  LinkData.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/28/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//
#include "linkdata.h"
using namespace std;

LinkData::LinkData() {
    linkID = 0;
    bandwidth = 0.0;
    lengthKM = 0.0;
    velocity = 0.0;
    noisePower = 0.0;
}

LinkData::LinkData(vector<string> *tokens) {
    setProperties(tokens);
}

void LinkData::setProperties(vector<string> *tokens) {
    int i = 0;
    for (vector<string>::iterator it = tokens->begin();
         it != tokens->end(); it++) {
        
        if (i == 0) {
            linkID = stoi(*it);
        } else if (i == 1) {
            bandwidth = stof(*it);
        } else if (i == 2) {
            lengthKM = stof(*it);
        } else if (i == 3) {
            velocity = stof(*it);
        } else if (i == 4) {
            noisePower = stof(*it);
        }
        i++;
    }
}

int LinkData::id() {
    return linkID;
}

string LinkData::getDataString() {
    return to_string(linkID) + "," +
    to_string(bandwidth) + "," +
    to_string(lengthKM) + "," +
    to_string(velocity) + "," +
    to_string(noisePower);
}

