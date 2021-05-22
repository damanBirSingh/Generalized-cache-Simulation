#include<bits/stdc++.h>
#include "cache.hpp"

bool containsTag(list<cache> set, int req_tag);
void add_block_to_set_associative_cache(map<int, list<cache>> &, int , int , int , int);
void find_oldest_block_in_that_set(list<cache>, list<int>, int);
void replace_block_in_set_associative_cache(map<int, list<cache>> &, int , int , int , int);

void cache_impl::retrieve_value_from_set_associative_cache(int mem_addr){
    int mem_tag, mem_set, mem_block_offset, key;

    int set_bits = log2(num_sets);
    int tag_bits = log2(mem_addr) - block_offset_bits + set_bits;
    
    mem_block_offset = (mem_addr) & (int)(pow(2,block_offset_bits) - 1);
    mem_set = (mem_addr>>block_offset_bits) & (int)(pow(2,set_bits) - 1);
    mem_tag = (mem_addr>>(set_bits + block_offset_bits)) & (int)(pow(2,tag_bits) - 1);
    key = (mem_addr>>block_offset_bits) & (int)(pow(2,set_bits + tag_bits) - 1);
    cout<<"Tag: "<<mem_tag<<" Set: "<<mem_set<<endl;
    if( (set_associative_cache.find(mem_set) != set_associative_cache.end()) && //address wrt line
        containsTag((set_associative_cache.find(mem_set)->second), mem_tag) ) { // in that line, compare tag
        hit++;
        cout<<"Is a Hit";
    } else {
        cout<<"Is a Miss";
        miss++;
        if((set_associative_cache.find(mem_set) != set_associative_cache.end()) &&
            (set_associative_cache.find(mem_set)->second).size() == 2)
            replace_block_in_set_associative_cache(set_associative_cache, mem_tag, mem_set, mem_addr, block_size);
        else
            add_block_to_set_associative_cache(set_associative_cache, mem_tag, mem_set, mem_addr, block_size);
    }

}

bool containsTag(list<cache> set, int req_tag){
    for(cache val: set){
        if(val.tag == req_tag)
            return true;
    }
    return false;
}

void add_block_to_set_associative_cache(map<int, list<cache>> &set_associative_cache, int tag, int set, int mem_addr, int block_size){
    cache block;
    block.tag = tag;
    block.validBit = 1;
    block.data = decimal_to_hex_string(mem_addr);
    set_associative_cache[set].push_front(block);
}


void replace_block_in_set_associative_cache(map<int, list<cache>> &set_associative_cache, int tag, int set, int mem_addr, int block_size){
    set_associative_cache[set].pop_back();
    add_block_to_set_associative_cache(set_associative_cache, tag, set, mem_addr, block_size);
}