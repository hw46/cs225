#include "cs225/PNG.h"

#include "sketching.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <map>
#include <set>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;

vector<uint64_t> kminhash(vector<int> inList, unsigned k, hashFunction h){
    set<uint64_t> set;
    vector<uint64_t> minHash;
    for(auto i:inList){
        set.insert(h(i));
    }
    if(k<inList.size()){
        unsigned i=0;
        for(auto it=set.begin(); i<k && it!=set.end(); i++, ++it){
            minHash.push_back(*it);
        }
    }
    else{
        unsigned i=0;
        for(auto it=set.begin(); i<k && it!=set.end(); i++, ++it){
            minHash.push_back(*it);
        }
        for(unsigned x=0; x<k-inList.size(); x++){
            minHash.push_back(GLOBAL_MAX_INT);
        }
    }
    if(minHash.size()==1){
        minHash.push_back(GLOBAL_MAX_INT);
    }
    return minHash;
}

vector<uint64_t> khash_minhash(vector<int> inList, vector<hashFunction> hv){
    vector<uint64_t> kHash(hv.size(), numeric_limits<uint64_t>::max());
    for(int i:inList){
        for(size_t j = 0; j < hv.size(); j++){
            if(hv[j](i) < kHash[j]){
                kHash[j] = hv[j](i);
            }
        }
    }
    return kHash;
}

vector<uint64_t> kpartition_minhash(vector<int> inList, int part_bits, hashFunction h){
    vector<uint64_t> min(pow(2,part_bits), GLOBAL_MAX_INT);
    for(int i:inList){
        if(h(i)<min[h(i)>>(64-part_bits)]){
            min[h(i)>>(64-part_bits)]=h(i);
        }
    }
    return min;
}

float minhash_jaccard(vector<uint64_t> mh1, vector<uint64_t> mh2){

    set<uint64_t> set;
    for(auto i:mh1){
        set.insert(i);
    }
    for (auto i:mh2){
        set.insert(i);
    }
    return (float)(mh1.size()+mh2.size()-set.size())/(float)(set.size());
}

int minhash_cardinality(vector<uint64_t> mh, unsigned k){
    return ceil((float)k/((float)mh[k-1]/(float)GLOBAL_MAX_INT)-1);
}

float exact_jaccard(vector<int> raw1, vector<int> raw2){
    set<int> set1;
    set<int> set2;
    for(unsigned i=0; i<raw1.size(); i++){
        set1.insert(raw1[i]);
    }
    for(unsigned i=0; i<raw2.size(); i++){
        set2.insert(raw2[i]);
    }
    vector<int> intersection(max(set1.size(), set2.size()),0);
    vector<int>::iterator it=set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), intersection.begin());
    intersection.resize(it-intersection.begin());
    return (float)(intersection.size())/(float)(set1.size()+set2.size()-intersection.size());
}

int exact_cardinality(vector<int> raw){
    set<int> set(raw.begin(), raw.end());
    return set.size();
}

MM::MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h){
    minHashes.resize(numTiles*numTiles);
    tileWidth=ceil((double)input.width()/numTiles);
    tileHeight=ceil((double)input.height()/numTiles);
    tileNum=numTiles;
    for(unsigned x=0; x<numTiles; x++){
        for(unsigned y=0; y<numTiles; y++){
            vector<int> tileData;
            for(unsigned i=x*tileWidth; i<input.width() && i<(x+1)*tileWidth; i++){
                for(unsigned j=y*tileHeight; j<input.height() && j<(y+1)*tileHeight; j++){
                    cs225::BWPixel pixel=input.getPixel(i,j);
                    tileData.push_back((int)(pixel.l*255));
                }
            }
            vector<uint64_t> minHashVec=kminhash(tileData,k,h);
            minHashes[y*numTiles+x]=minHashVec;
        }
    }
}

vector<uint64_t> MM::getMinHash(unsigned width, unsigned height) const{
    return minHashes[height*tileNum+width];
}

int MM::countMatchTiles(const MM & other, float threshold) const{
    int count=0;
    for(size_t i=0; i<minHashes.size(); i++){
        float similarity=minhash_jaccard(minHashes[i],other.minHashes[i]);
        if(threshold<=similarity){
            count++;
        }
    }
    return count;
}

vector<tuple<int, int, int>> build_minhash_graph(vector<string> flist, unsigned numTiles, unsigned k, hashFunction h, float threshold){
    vector<MM> pic;
    for(auto i:flist){
        cs225::PNG PNG;
        PNG.readFromFile(i);
        pic.push_back(MM(PNG,numTiles,k,h));
    }
    vector<tuple<int,int,int>> result;
    for(unsigned i=0; i<flist.size(); i++){
        for(unsigned j=i+1; j<flist.size(); j++){
            result.push_back(tuple(i,j,pic[i].countMatchTiles(pic[j],threshold)));
        }
    }
    return result;
}