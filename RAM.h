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
 *  2) Ian Stephenson, changed signature of initializeRAM to take const string&
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
    RAM();

    /*
     * Function: initializeRAM
     *      Read in contents form input.txt and store them into the storage vector
     */
    void InitializeRAM(const string& filename);

    /*
     * Function: MemoryView
     *
     */
    void MemoryView();

    /*
     * Function: MemoryDump
     */
    void MemoryDump();

};

#endif //CACHESIMULATOR_RAM_H
