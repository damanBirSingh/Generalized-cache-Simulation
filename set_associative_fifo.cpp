#include "cache.hpp"

bool containsTag (deque<cache> qtemp, int atag){
    for(int i=0;i<qtemp.size();i++){
        if(atag == qtemp[i].tag)
        return true;
    }
    return false;
}

void cache_impl::retrieve_value_from_set_associative_cache_FIFO(int address){
    int atag, setBits, offsetBits;

    offsetBits = log2(block_size*4);
    setBits = log2(num_sets);
 
    int x = offsetBits + setBits;

    int temp = block_size;

    int whichSet = ((address)>>offsetBits) & (num_sets-1);
    atag = (address) >> x;

    if(set_associative_cache_FIFO[whichSet][0].validBit == 1){

        if(containsTag(set_associative_cache_FIFO[whichSet], atag)){
            hit++;
        } else{
            miss++;
            if(set_associative_cache_FIFO[whichSet].size() < (set_ways*block_size)){
                while(temp>0){
                    set_associative_cache_FIFO[whichSet].push_back(cache(1,atag,decimal_to_hex_string(address)));
                    temp--;
                    address += word_size;
                }
            } else{
                while(temp > 0){
                    set_associative_cache_FIFO[whichSet].pop_front();
                    set_associative_cache_FIFO[whichSet].push_back(cache(1,atag,decimal_to_hex_string(address)));
                    temp--;
                    address += word_size;

                }
            }
        }
    }
    else{
        set_associative_cache_FIFO[whichSet].clear();
        miss++;
        deque<cache> q;
        while(temp>0){
            q.push_back(cache(1, atag , decimal_to_hex_string(address)));
            set_associative_cache_FIFO[whichSet] = q;
            temp--;
        }
    }
}      
    

