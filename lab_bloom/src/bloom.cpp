/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"

BF::BF(uint64_t size, std::vector<hashFunction> hashList){
    // Your code here
    bv.resize(size, false);
    hv = hashList;
}

BF::BF(const BF& other){
    // Your code here
    hv = other.hv;
    bv = other.bv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){
    // Your code here
    for (auto & func : hv) { // Loop over the hash functions
        int hashValue = func(key); // Compute hash value for the key
        bv[hashValue % bv.size()] = true; // Set the corresponding bit to true
    }
}

bool BF::contains(const int& key) const{
    // Your code here 
    for (auto & func : hv) { // Loop over the hash functions
        int hashValue = func(key); // Compute hash value for the key
        if (!bv[hashValue % bv.size()]) // Check if the corresponding bit is false
            return false; // If any bit is false, the key is definitely not present
    }
    return true;
}

void BF::bit_union(const BF& other){
    // Your code here 
    for (size_t i = 0; i < bv.size(); ++i) {
        bv[i] = bv[i] || other.bv[i]; // Perform bitwise OR on each bit
    }
}

void BF::intersect(const BF& other){
    // Your code here 
    for (size_t i = 0; i < bv.size(); ++i) {
        bv[i] = bv[i] && other.bv[i]; // Perform bitwise AND on each bit
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here
    BF bf(size, hashList);
    for(size_t i = 0; i < inList.size(); i++){
        bf.add(inList[i]);
    }

    int falsePositives = 0;
    int trueNegatives = 0;
    for (unsigned int i = 0; i < max; i++) {
        if(std::find(inList.begin(), inList.end(), i) == inList.end()){
            if(bf.contains(i)){
                falsePositives++;
            }
            else{
                trueNegatives++;
            }
        }
    }

    // Assuming max is the total number of elements checked.
    return static_cast<float>(falsePositives) / (falsePositives + trueNegatives);
}

bool getBitFromArray(std::vector<char> bv, int index){
    // Your code here
    int charIndex = index / 8;

    // Find the position of the bit within the character
    int bitIndex = index % 8;

    // Retrieve the character that contains the desired bit
    char byte = bv[charIndex];

    // Shift the bits of the character to the right so that the bit we're interested in is the least significant bit
    // Then, perform a bitwise AND with 1 to isolate the least significant bit
    return (byte >> (7 - bitIndex)) & 0x01;
}

bool getBitFromByte(char in, int index){
    // Your code here
    int a =0;
    int bindex = index%8;
    return (in >> (7-bindex)) & 0x01; // Shift the bit to the rightmost position and mask with 1
}