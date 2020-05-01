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
#include <string>
#include <iomanip>
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

/*
 * MemoryView
 */
void RAM::MemoryView()
{
    cout << "memory-view" << endl;

    cout << "memory_view:" << storage.size() << endl;

    cout << "memory_content:" << endl;

    cout << "Address Data" << endl;

    const int MEM_BLOCK = 8;

    for (size_t i = 0; i < storage.size(); i+= MEM_BLOCK)
    {
        cout << "0x" << setfill('0') << setw(2) << hex << uppercase << i << ' ';

        for (size_t j = i; j < (i + MEM_BLOCK); j++)
        {
            string hexData = storage[j];
            cout << setfill('0') << setw(2) << hex << uppercase << hexData << ' ';
        }

        cout << endl;
    }

}

/*
 * MemoryDump
 */
void RAM::MemoryDump()
{
    ofstream fout("ram.txt");

    for (auto& address : storage)
    {
        string numAddr = address;

        fout << setfill('0') << setw(2) << hex << uppercase << numAddr << endl;
    }

    fout.close();
}