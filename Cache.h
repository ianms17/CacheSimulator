/*
 * Project: Cache Simulator
 * Authors: Ian Stephenson, Paul Shin
 * File: Cache.cpp
 *      Description: Prototype of the Cache object
 * CSCE 312, Spring 2020
 */

/*
 * CHANGELOG
 *  1) Ian Stephenson, Initial Commit
 *  2) Ian Stephenson, altered signature of parametrized constructor
 *  3) Ian Stephenson, changed name of data member in dataLine
 *  4) Ian Stephenson, added data members hit and miss counter, added tagBits to dataLine struct
 */

#ifndef CACHESIMULATOR_CACHE_H
#define CACHESIMULATOR_CACHE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct dataLine {
    string data;
    string tagBits;
    char validBit;
    char dirtyBit;
    int accessCounter;
};

class Cache {

private:

    /*
     * Private Data Members
     */
    int cacheSize;
    int dataBlockSize;
    int associativity;
    int replacementPolicy;
    int writeHitPolicy;
    int writeMissPolicy;
    const unsigned int addressWidth = 8;
    int hitCounter;
    int missCounter;
    vector<vector<dataLine>> cacheStore;

    /*
     * Private Helper Functions
     */
    int CalculateTagBits(int m, int s, int b);
    int CalculateBlockOffsetBits(int B);
    int CalculateSetIndexBits(int S);
    int CalculateSetLines(int C, int B, int S);



public:

    /*
     * Default Constructor
     */
    Cache();

    /*
     * Parametrized Constructor
     */
    Cache(int C, int B, int S, int replacement, int writeHit, int writeMiss);

    /*
     * Function: CacheRead
     *
     */
    void CacheRead();

    /*
     * Function: CacheWrite
     *
     */
    void CacheWrite(string address, string data);

    /*
     * Function: CacheFlush
     *
     */
    void CacheFlush();

    /*
     * Function: CacheView
     *
     */
    void CacheView();

    /*
     * Function: CacheDump
     *
     */
    void CacheDump();


};

#endif //CACHESIMULATOR_CACHE_H
