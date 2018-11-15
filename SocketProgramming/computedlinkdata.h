//
//  ComputedLinkData.hpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#ifndef computedlinkdata_h
#define computedlinkdata_h

#include <stdio.h>
#include <string>
#include <math.h>
#include "linkdata.h"
#endif /* ComputedLinkData_hpp */

/**
 * Represent a computable link data (delay)
 */
class ComputedLinkData : public LinkData {
public:
    static double dbmToWatts(double);
    static double roundTo2ndDecimal(double);

    ComputedLinkData();
    ComputedLinkData(int, float, float, float, float, float, float);
    ComputedLinkData(std::vector<std::string> *tokens);
    void compute();
    
    double transmissionDelay() {
        return roundTo2ndDecimal(transmissionTime);
    }
    
    double propagationDelay() {
        return roundTo2ndDecimal(propagationTime);
    }
    
    double endToEndDelay() {
        return roundTo2ndDecimal(transmissionTime + propagationTime);
    }
    
    float fileSize() {
        return packetSize;
    }
    
    float power() {
        return signalPower;
    }
    
    std::string getDelayString();

private:
    // given by users
    float packetSize;
    float signalPower;
    
    // computed result
    double capacity;
    double transmissionTime;
    double propagationTime;
    
    void computeCapacity();
    void computeTransmissionDelay();
    void computePropagationDelay();
};
