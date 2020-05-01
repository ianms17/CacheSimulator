/*
 * Project: Cache Simulator
 * Authors: Ian Stephenson, Paul Shin
 * File: Cache.cpp
 *      Description: Implementation of the Cache object
 * CSCE 312, Spring 2020
 */

/*
 * CHANGELOG
 *  1) Ian Stephenson, Initial Commit
 *  2) Ian Stephenson, implemented Private Helper Functions listed in Cache.h, implemented constructors
 *  3) Ian Stephenson, completed the parametrized constructor to initialize cacheStore vector
 *  4) Ian Stephenson, implemented cacheView and cacheDump, tested for basic functionality but no edge cases
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include <bitset>
#include <fstream>
#include "Cache.h"


/*
 * Default Constructor
 */
Cache::Cache()
    : cacheSize(0), dataBlockSize(0), associativity(0), replacementPolicy(0), writeHitPolicy(0),
      writeMissPolicy(0), addressWidth(8), cacheStore(0), hitCounter(0), missCounter(0) {}

/*
 * Parametrized Constructor
 *      Constructor will be called in the main function after getting info from cache configurator
 */
Cache::Cache(int C, int B, int S, int replacement, int writeHit, int writeMiss) {
    cacheSize = C;
    dataBlockSize = B;
    associativity = S;
    replacementPolicy = replacement;
    writeHitPolicy = writeHit;
    writeMissPolicy = writeMiss;

    hitCounter = 0;
    missCounter = 0;

    // calculate values for bits in cacheStore
    int E = CalculateSetLines(C, B, S);
    // int s = CalculateSetIndexBits(S);
    // int b = CalculateBlockOffsetBits(B);
    // int t = CalculateTagBits(addressWidth, s, b);

    /*
     * cacheStore contains a vector of vector of dataLines, each inner vector
     * is a set in the n way associative cache, so we need S inner vectors to
     * represent our associative cache
     */
    cacheStore.resize(S);

    // initialize cacheStore with default cacheLines
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < E; ++j) {
            // struct dataLine, signature found in Cache.h
            dataLine defaultData;

            // initialize all bits and counter to 0, push onto vector at vector[i][j]
            defaultData.data = "00000000";
            defaultData.validBit = '0';
            defaultData.dirtyBit = '0';
            defaultData.accessCounter = 0;
            defaultData.tagBits = "00";
            cacheStore.at(i).push_back(defaultData);
        }
    }
}


/*
 * Private Helper Function: CalculateTagBits
 */
int Cache::CalculateTagBits(int m, int s, int b) {
    // Formula given by t = m - (s + b) on slide 39 of the notes
    return m - (s + b);
}

/*
 * Private Helper Function: CalculateBlockOffsetBits
 */
int Cache::CalculateBlockOffsetBits(int B) {
    // Formula given by b = log_2(B) in slides, if an interger is return from log, get next highest integer
    return ceil(log2(B));
}

/*
 * Private Helper Function: CalculateSetIndexBits
 */
int Cache::CalculateSetIndexBits(int S) {
    // Formula given by s = log_2(S), ceil to get next highest integer if it is a decimal
    return ceil(log2(S));
}

/*
 * Private Helper Function: CalculateSetLines
 */
int Cache::CalculateSetLines(int C, int B, int S) {
    // Formula given by C = B * E * S, solving for E, E = C / (B * S)
    return ceil(C / (B * S));
}

/*
 * CacheWrite
 */
void Cache::CacheWrite(string address, string data) {
    // convert address to binary
    address = "0x" + address;
    stringstream ss;
    ss << hex << address;
    string num;
    ss >> num;
    bitset<8> b(num);

    // get tag bits, block offsets, and set index
    int setIndex = CalculateSetIndexBits(associativity);
    int blockOffset = CalculateBlockOffsetBits(dataBlockSize);
    int tagBits = CalculateTagBits(addressWidth, setIndex, blockOffset);

    // get string values from the address passed in
    string tagString = num.substr(0, tagBits);
    string setString = num.substr(tagBits, setIndex);

    // output stuff
    cout << "set:" << setString << endl;
    cout << "tag:" << tagString << endl;
    cout << "write-hit:no" << endl;
    cout << "eviction-line:0" << endl;
    cout << "ram_address:" << address << endl;
    cout << "data:" << data << endl;
    cout << "dirty_bit:1" << endl;
}

/*
 * CacheView
 */
void Cache::CacheView() {
    cout << "cache_size:" << cacheSize << endl;
    cout << "data_block_size:" << dataBlockSize << endl;
    cout << "associativity:" << associativity << endl;
    // check input values for replacement values to determine which one was used
    if (replacementPolicy == 1) {
        cout << "replacement_policy:random_replacement"  << endl;
    } else if (replacementPolicy == 2) {
        cout << "replacement_policy:least_recently_used" << endl;
    }

    // branch check for write hit policy
    if (writeHitPolicy == 1) {
        cout << "write_hit_policy:write_through" << endl;
    } else if (writeHitPolicy == 2) {
        cout << "write_hit_policy:write_back" << endl;
    }

    // branch check for write miss policy
    if (writeMissPolicy == 1) {
        cout << "write_miss_policy:write_allocate" << endl;
    } else if (writeMissPolicy == 2) {
        cout << "write_miss_policy:no_write_allocate" << endl;
    }

    cout << "number_of_cache_hits:" << hitCounter << endl;
    cout << "number_of_cache_misses:" << missCounter << endl;
    cout << "cache_content:" << endl;

    // output loop for cache contents
    for (int i = 0; i < associativity; ++i) {
        for (int j = 0; j < CalculateSetLines(cacheSize, dataBlockSize, associativity); ++j) {
            cout << cacheStore.at(i).at(j).validBit << " ";
            cout << cacheStore.at(i).at(j).dirtyBit << " ";
            cout << cacheStore.at(i).at(j).tagBits << " ";

            // need spaces between bytes, get substrings of data string
            string byte1 = cacheStore.at(i).at(j).data.substr(0, 2);
            string byte2 = cacheStore.at(i).at(j).data.substr(2, 2);
            string byte3 = cacheStore.at(i).at(j).data.substr(4, 2);
            string byte4 = cacheStore.at(i).at(j).data.substr(6, 2);

            // output the data with spaces between bytes
            cout << byte1 << " " << byte2 << " " << byte3 << " " << byte4 << endl;
        }
    }
}

/*
 * CacheDump
 */
void Cache::CacheDump() {
    ofstream ofs;
    ofs.open("Cache.txt");

    for (int i = 0; i < associativity; ++i) {
        for (int j = 0; j < CalculateSetLines(cacheSize, dataBlockSize, associativity); ++j) {
            ofs << cacheStore.at(i).at(j).validBit << " ";
            ofs << cacheStore.at(i).at(j).dirtyBit << " ";
            ofs << cacheStore.at(i).at(j).tagBits << " ";

            // need spaces between bytes, get substrings of data string
            string byte1 = cacheStore.at(i).at(j).data.substr(0, 2);
            string byte2 = cacheStore.at(i).at(j).data.substr(2, 2);
            string byte3 = cacheStore.at(i).at(j).data.substr(4, 2);
            string byte4 = cacheStore.at(i).at(j).data.substr(6, 2);

            // output the data with spaces between bytes
            ofs << byte1 << " " << byte2 << " " << byte3 << " " << byte4 << endl;
        }
    }
    ofs.close();
}

/*
 * CacheFlush
 */
void Cache::CacheFlush() {
    cacheStore.clear();
}
