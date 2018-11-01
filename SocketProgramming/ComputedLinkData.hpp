//
//  ComputedLinkData.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef ComputedLinkData_hpp
#define ComputedLinkData_hpp

#include <stdio.h>
#include <string>
#include <math.h>
#include "LinkData.hpp"
#endif /* ComputedLinkData_hpp */


class ComputedLinkData : public LinkData {
public:
    static double dbmToWatts(double);
    
    ComputedLinkData();
    ComputedLinkData(int, float, float, float, float, float, float);
    ComputedLinkData(vector<string> *tokens);
    void compute();
    
    double transmissionDelay() {
        return transmissionTime;
    }
    
    double propagationDelay() {
        return propagationTime;
    }
    
    double endToEndDelay() {
        return transmissionDelay() + propagationDelay();
    }
    
    float fileSize() {
        return packetSize;
    }
    
    float power() {
        return signalPower;
    }
    
    string getDelayString();

private:
    float packetSize;
    float signalPower;
    double capacity;
    double transmissionTime;
    double propagationTime;
    
    void computeCapacity();
    void computeTransmissionDelay();
    void computePropagationDelay();
};
