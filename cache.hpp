#ifndef CACHE_HEADER
#define CACHE_HEADER

#include<bits/stdc++.h>

using namespace std;
enum replacement_algo {FIFO = 1, LRU = 2}; 
enum cache_type {direct_mapped = 1, fully_associative = 2, set_associative = 3}; 

string decimal_to_hex_string(int);

struct cache{
    int validBit;
    int tag;
    string data;

    cache(){}
    cache(int validBit, int tag, string data)
    : validBit(validBit), tag(tag), data(data) {}
};

class cache_impl{
    public:
    int block_size; // in words
    int num_sets;
    int set_ways;
    int cache_size; //in words
    int num_lines;
    int block_offset_bits;
    cache_type c_type;
    replacement_algo repl_algo;

    vector<int> address;
    ifstream file;
    
    map<int, cache> direct_cache; // map<line_num, cache>

    map<int, list<cache>> set_associative_cache; // map<set_num, list of values in the set>
    
    vector<deque<cache>> set_associative_cache_FIFO;

    map<int, cache> fully_associative_cache; // map<tag, cache>
    list<int> fa_keys;

    int miss = 0, hit = 0;
    cache_impl();
    void set_cache_parameters(int, int, int);
    void retrieve_value_from_direct_cache(int);
    void retrieve_value_from_set_associative_cache_LRU(int);
    void retrieve_value_from_set_associative_cache_FIFO(int);
    void retrieve_value_from_fully_associative_cache_LRU(int);
    //void retrieve_value_from_fully_associative_cache_FIFO(int);
    void call_appropriate_cache(int);
    void print_appropriate_cache_state();
    ~cache_impl();
};

#endif


