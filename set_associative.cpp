#include<bits/stdc++.h>

bool containsTag(list<struct cache>> set, int req_tag);
void add_block_to_set_associatice_cache(map<int, struct cache> &, int , int , int , int)


void cache_impl::retrieve_value_from_set_associative_cache(int mem_addr){
    
    int mem_tag, mem_set, mem_block_offset, key;

    int set_bits = log2(num_sets);
    int tag_bits = log2(mem_addr) - block_offset_bits + set_bits;
    
    mem_block_offset = (mem_addr) & (int)(pow(2,block_offset_bits) - 1);
    mem_set = (mem_addr>>block_offset_bits) & (int)(pow(2,set_bits) - 1);
    mem_tag = (mem_addr>>(line_bits + block_offset_bits)) & (int)(pow(2,tag_bits) - 1);
    key = (mem_addr>>block_offset_bits) & (int)(pow(2,set_bits + tag_bits) - 1);

    if( (set_associative_cache.find(mem_set) != set_associative_cache.end()) && //address wrt line
        containsTag((set_associative_cache.find(mem_line)->second), mem_tag) ) { // in that line, compare tag
        hit++;
        tag_set_key.erase(key);
        tag_set_key.push_front(key);
    } else {
        miss++;
        if((set_associative_cache.find(mem_set) != direct_cache.end() &&
            set_associative_cache.find(mem_set).size() == 2)
            find_oldest_block_in_that_set()
            replace_block_in_set_associative_cache();
        else
            add_block_to_cache(set_associative_cache, mem_tag, mem_set, mem_addr, block_size);
            tag_set_key.push_front(key);
    }

}


bool containsTag(list<struct cache>> set, int req_tag){
    for(cache val: set){
        if(val.tag == req_tag)
            return true;
    }
    return false;
}

void add_block_to_set_associatice_cache(map<int, struct cache> &set_associative_cache, int tag, int set, int mem_addr, int block_size){
    cache block;
    block.tag = tag;
    block.validBit = 1;
    block.data = decimal_to_hex_string(mem_addr);
    set_associative_cache.find(mem_set).push_front(block);
}

void replace_block_in_set_associative_cache(){

}