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
 */

#include <iostream>
#include <cmath>
#include "Cache.h"


/*
 * Default Constructor
 */
Cache::Cache()
    : cacheSize(0), dataBlockSize(0), associativity(0), replacementPolicy(0), writeHitPolicy(0),
      writeMissPolicy(0), addressWidth(8), cacheStore(0) {}

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

    // address width always has a hard coded value of 8 bits
    addressWidth = 8;

    /*
     * cacheStore contains a vector of vector of dataLines, each inner vector
     * is a set in the n way associative cache, so we need S inner vectors to
     * represent our associative cache
     */
    cacheStore.resize(S);
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
