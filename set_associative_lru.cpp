#include "cache.hpp"

bool containsTag(list<cache> set, int req_tag);
void add_block_to_set_associative_cache(map<int, list<cache>> &, int , int , int , int);
void find_oldest_block_in_that_set(list<cache>, list<int>, int);
void replace_block_in_set_associative_cache(map<int, list<cache>> &, int , int , int , int);

void cache_impl::retrieve_value_from_set_associative_cache_LRU(int address){
    int mem_tag, mem_set, mem_block_offset, key;

    int set_bits = log2(num_sets);
    
    mem_block_offset = (address) & (int)(pow(2,block_offset_bits) - 1);
    mem_set = (address>>block_offset_bits) & (int)(pow(2,set_bits) - 1);
    mem_tag = (address>>(set_bits + block_offset_bits));

    //cout<<"Tag: "<<mem_tag<<" Set: "<<mem_set<<endl;
    if( (set_associative_cache.find(mem_set) != set_associative_cache.end()) && //address wrt line
        containsTag((set_associative_cache.find(mem_set)->second), mem_tag) ) { // in that line, compare tag
        hit++;
        auto itr = set_associative_cache[mem_set].begin();
        while (itr != set_associative_cache[mem_set].end() ) {
            //cout << *itr << " ";
            if(itr->tag == mem_tag)
                break;
            itr++;
        }
        set_associative_cache[mem_set].erase(itr);
        add_block_to_set_associative_cache(set_associative_cache, mem_tag, mem_set, address, block_size);
        //push this block to the front
        //cout<<"Is a Hit\n";
    } else {
        //cout<<"Is a Miss\n";
        miss++;
        if((set_associative_cache.find(mem_set) != set_associative_cache.end()) &&
            (set_associative_cache.find(mem_set)->second).size() == set_ways)
            replace_block_in_set_associative_cache(set_associative_cache, mem_tag, mem_set, address, block_size);
        else
            add_block_to_set_associative_cache(set_associative_cache, mem_tag, mem_set, address, block_size);
    }

}

bool containsTag(list<cache> set, int req_tag){
    for(cache val: set){
        if(val.tag == req_tag)
            return true;
    }
    return false;
}

void add_block_to_set_associative_cache(map<int, list<cache>> &set_associative_cache, int tag, int set, int address, int block_size){
    //cache block;
    //block.tag = tag;
    //block.validBit = 1;
    string data = decimal_to_hex_string(address);
    if(block_size == 2)
        data += " "+  decimal_to_hex_string(address + 4);
    set_associative_cache[set].push_front(cache(1, tag, data));
}

void replace_block_in_set_associative_cache(map<int, list<cache>> &set_associative_cache, int tag, int set, int address, int block_size){
    set_associative_cache[set].pop_back();
    add_block_to_set_associative_cache(set_associative_cache, tag, set, address, block_size);
}