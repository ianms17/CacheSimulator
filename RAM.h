/*
 * Project: Cache Simulator
 * Authors: Ian Stephenson, Paul Shin
 * File: RAM.h
 *      Description: Prototype of the RAM object
 * CSCE 312, Spring 2020
 */

/*
 * CHANGELOG
 *  1) Ian Stephenson, Initial Commit
 *
 */

#ifndef CACHESIMULATOR_RAM_H
#define CACHESIMULATOR_RAM_H

#include <iostream>
#include <vector>

using namespace std;

class RAM {

    // declare Cache as a friend in order to access storage without copying
    friend class Cache;

private:
    vector<string> storage;

public:

    /*
     * Function: RAM constructor, initialize vector to hold bytes
     */
    RAM() {
        storage.resize(256);
    }

    /*
     * Function: initializeRAM
     *      Read in contents form input.txt and store them into the storage vector
     */
    void InitializeRAM(string filename);
};

#endif //CACHESIMULATOR_RAM_H
