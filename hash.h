#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
	const int NUM_BLOCKS = 5;
	const int BLOCK_SIZE = 6;
	unsigned long long w[NUM_BLOCKS] = { 0 };
	int n = static_cast<int>(k.size());
	for(int i=0; i<NUM_BLOCKS; ++i) {
		long long startIndex = n-BLOCK_SIZE*(i+1);
		unsigned long long blockValue = 0;
		for(int j=0; j<BLOCK_SIZE; ++j) {
			int idx = static_cast<int>(startIndex+j);
			unsigned long long v = 0;
			if(idx>=0 && idx<n) v = letterDigitToNumber(k[idx]);
			blockValue = blockValue * 36ULL + v;
		}
		w[NUM_BLOCKS - 1 - i] = blockValue;
	}
	unsigned long long h=0;
	for(int i=0; i<NUM_BLOCKS; ++i) {
		h+= static_cast<unsigned long long>(rValues[i]) * w[i];
	}
	return static_cast<HASH_INDEX_T>(h);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
	if(std::isdigit(static_cast<unsigned char>(letter))) return static_cast<HASH_INDEX_T>(letter - '0' + 26);
	letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
	if(letter >= 'a' && letter <= 'z') return static_cast<HASH_INDEX_T>(letter-'a');
	return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
