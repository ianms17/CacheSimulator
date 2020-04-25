/*
 * Project: Cache Simulator
 * File: RAM.cpp
 *      Implementation of the RAM object
 * Authors: Ian Stephenson, Paul Shin
 * CSCE 312, Spring 2020
 */

/*
 * CHANGELOG
 *  1) Ian Stephenson, Initial Commit
 *  2) Ian Stephenson, implemented constructor and initializeRAM file reader
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "RAM.h"

using namespace std;

/*
 * Constructor
 */
RAM::RAM() {
    storage.resize(256);
}

/*
 * Initialize RAM
 */
void RAM::InitializeRAM(const string& filename) {
    ifstream ifs;
    ifs.open(filename);
    if (!ifs) {
        throw invalid_argument("Could not open file");
    } else {
        string data;
        while (!ifs.eof()) {
            ifs >> data;
            storage.push_back(data);
        }
    }
}