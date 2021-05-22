#ifndef CACHE_HEADER
#define CACHE_HEADER

#include<bits/stdc++.h>

using namespace std;
//enum replacement_algo {FIFO = 0, LRU = 1}; 
//enum cache_implementation {direct_mapped = 0, fully_associated = 1, set_associative = 2}; 

string decimal_to_hex_string(int);

struct cache{
    int validBit;
    int tag;
    string data;
    //cache(int validBit, int tag, int data)                                    
    //: validBit(validBit), tag(tag), data(data) {}
};

class cache_impl{
    public:
    int block_size; // in words
    int num_sets;
    int set_ways;
    int cache_size; //in words
    int num_lines;
    int block_offset_bits;
    
    //cache_implementation cache_impl;
    //replacement_algo repl_algo;
    vector<int> address;
    ifstream file;
    map<int, cache> direct_cache; // map<line_num, cache>

    map<int, list<cache>> set_associative_cache; // map<set_num, list of values in the set>
    list<int> tag_set_key;

    int miss = 0, hit = 0;
    cache_impl();
    void set_cache_parameters(int, int, int);
    void retrieve_value_from_direct_cache(int);
    void retrieve_value_from_set_associative_cache(int);
    ~cache_impl();
};

#endif


