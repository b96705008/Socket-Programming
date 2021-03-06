//
//  ComputedLinkData.cpp
//  SocketProgramming
//
//  Created by Tai-Yi Kuo on 10/29/18.
//  Copyright © 2018 Tai-Yi Kuo. All rights reserved.
//

#include "computedlinkdata.h"
using namespace std;

/**
 * Transform dbm to watts
 * @param dbm value in dbm
 * @return value in watts
 */
double ComputedLinkData::dbmToWatts(double dbm) {
    double exp = dbm / 10.0;
    return pow(10.0, exp) / 1000.0;
}

double ComputedLinkData::roundTo2ndDecimal(double value) {
    return round(value * 100) / 100.0;
}

ComputedLinkData::ComputedLinkData() {
    packetSize = 0.0;
    signalPower = 0.0;
    capacity = 0.0;
    transmissionTime = 0.0;
    propagationTime = 0.0;
}

ComputedLinkData::ComputedLinkData(int id, float _bandwidth, float _length, float _velocity, float _noise, float _size, float _signal) {
    linkID = id;
    bandwidth = _bandwidth;
    lengthKM = _length;
    velocity = _velocity;
    noisePower = _noise;
    packetSize = _size;
    signalPower = _signal;
}

ComputedLinkData::ComputedLinkData(vector<string> *tokens) {
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
        } else if (i == 5) {
            packetSize = stof(*it);
        } else if (i == 6) {
            signalPower = stof(*it);
        }
        i++;
    }
    
    capacity = 0.0;
    transmissionTime = 0.0;
    propagationTime = 0.0;
}

/**
 * Compute Capacity using Shannon theorom
 */
void ComputedLinkData::computeCapacity() {
    double signalWatts = ComputedLinkData::dbmToWatts(static_cast<double>(signalPower));
    double noiseWatts = ComputedLinkData::dbmToWatts(static_cast<double>(noisePower));
    capacity = bandwidth * pow(10, 6) * log2(1 + signalWatts / noiseWatts);
}

/**
 * Compute Transmission Delay
 */
void ComputedLinkData::computeTransmissionDelay() {
    transmissionTime = packetSize / capacity * pow(10, 3);
}

/**
 * Compute Propagation Delay
 */
void ComputedLinkData::computePropagationDelay() {
    propagationTime = lengthKM / (velocity * 10.0);
}

/**
 * Compute all delay in proper sequence
 */
void ComputedLinkData::compute() {
    computeCapacity();
    computeTransmissionDelay();
    computePropagationDelay();
}

/**
 * Get delay message
 * @return delay message in CSV like
 */
string ComputedLinkData::getDelayString() {
    return to_string(transmissionDelay()) + "," +
        to_string(propagationDelay()) + "," +
        to_string(endToEndDelay());
}



