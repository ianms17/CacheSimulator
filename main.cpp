/*
 * Project: Cache Simulator
 * File: main.cpp
 *      Project driver
 * Authors: Ian Stephenson, Paul Shin
 * CSCE 312, Spring 2020
 */

/*
 * CHANGELOG
 *  1) Ian Stephenson, Initial Commit
 *  2) Ian Stephenson, Updated main function to initialize RAM and configure cache, created
 *                     skeleton of simulate cache without the function calls
 *  3) Ian Stephenson, added calls to cache view and dump, tested for basic functionality
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "RAM.h"
#include "Cache.h"

/*
 * Simulate the Cache Functions
 */
void printMenu() {
    cout << "*** Cache simulator menu ***" << endl;
    cout << "type one command:" << endl;
    cout << "1. cache-read" << endl;
    cout << "2. cache-write" << endl;
    cout << "3. cache-flush" << endl;
    cout << "4. cache-view" << endl;
    cout << "5. memory-view" << endl;
    cout << "6. cache-dump" << endl;
    cout << "7. memory-dump" << endl;
    cout << "8. quit" << endl;
    cout << "*******************" << endl;
}

int main() {

    string inFile = "input.txt";

    cout << "*** Welcome to the cache simulator ***" << endl;
    cout << "initialize the RAM:" << endl;
    cout << "init-ram 0x00 0xFF" << endl;

    /*
     * INITIALIZE RAM
     */
    // check that no exceptions were thrown when initializing RAM from file
    try {
        RAM simRAM;
        simRAM.InitializeRAM(inFile);
        cout << "ram successfully initialized" << endl << endl;
    } catch (exception& e) {
        cout << "Exception Caught: Error while Initializing RAM. TERMINATING" << endl;
    }

    // if no errors were caught, go on to configure the cache
    // create variables for parameterized constructor of Cache
    int C = 0;
    int B = 0;
    int S = 0;
    int rp = 0;
    int whp = 0;
    int wmp = 0;


    /*
     * CONFIGURE CACHE
     */
    // output in format given on project guidelines, take in input with prompts
    cout << "configure the cache:" << endl;
    try {
        cout << "cache size: " << endl;
        cin >> C;
        cout << "data block size: " << endl;
        cin >> B;
        cout << "associativity: " << endl;
        cin >> S;
        cout << "replacement policy: " << endl;
        cin >> rp;
        cout << "write hit policy: " << endl;
        cin >> whp;
        cout << "write miss policy: " << endl;
        cin >> wmp;
        cout << endl;
        // call parameterized constructor
        // Cache simCache(C, B, S, rp, whp, wmp);
    } catch (exception& e) {
        cout << "Exception Caught: Error while configuring cache. TERMINATING" << endl;
    }
    Cache simCache(C, B, S, rp, whp, wmp);

    /*
     * SIMULATE CACHE
     */
    string inputVal;
    try {
        while (inputVal != "quit") {
            printMenu();
            cin >> inputVal;
            if (inputVal == "cache-read") {
                string address;
                cin >> address;
            } else if (inputVal == "cache-write") {
                string address;
                string data;
                cin >> address;
                cin >> data;
            } else if (inputVal == "cache-flush") {
                cout << "cache_cleared" << endl;
            } else if (inputVal == "cache-view") {
                simCache.CacheView();
            } else if (inputVal == "memory-view") {
                cout << "memory_output" << endl;
            } else if (inputVal == "cache-dump") {
                simCache.CacheDump();
            } else if (inputVal == "memory-dump") {
                cout << "ram.txt holds output" << endl;
            } else if (inputVal == "quit") {
                break;
            } else {
                cout << "Invalid Command" << endl;
            }
        }
    } catch (exception& e) {
        cout << "Exception Caught: Error while simulating the cache" << endl;
    }

}
