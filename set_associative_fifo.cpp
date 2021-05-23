#include "cache.hpp"

/*struct cache{
    int validBit;
    int tag;
    int data;

    cache(int validBit, int tag, int data)
    : validBit(validBit), tag(tag), data(data) {}
};*/

//int miss = 0;
//int hit = 0;

bool containsTag (deque<cache> qtemp, int atag){
    for(int i=0;i<qtemp.size();i++){
        if(atag == qtemp[i].tag)
        return true;
    }
    return false;
}

void cache_impl::retrieve_value_from_set_associative_cache_FIFO(int address){
     //int lwAdd[25] = {0x40,0x44,0x48,0x4C,0x70,0x74,0x78,0x7C,0x80,0x84,0x88,0x8C,0x90,0x94,0x98,0x9C,0x0,0x4,0x8,0xC,0x10,0x14,0x18,0x1C,0x20};
    int atag, setBits, offsetBits;

    //int num_lines = ( cache_size / block_size);
    //int num_sets = (num_lines / set_ways);

    offsetBits = log2(block_size*4);
    setBits = log2(num_sets);
 
    //vector<deque<cache>> set_associative_cache_FIFO(num_sets, deque<cache>(set_ways*block_size, cache(0,0,0)));
 
    int x = offsetBits + setBits;

    int n = 400;
    int count=0;

//while(n--)
//{
    //for(int i=0;i<25;i++)
    //{
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
                }
            } else{
                while(temp > 0){
                    set_associative_cache_FIFO[whichSet].pop_front();

                    set_associative_cache_FIFO[whichSet].push_back(cache(1,atag,decimal_to_hex_string(address)));
                        temp--;

                }
            }
        }
    }
    else{
        set_associative_cache_FIFO[whichSet].clear();
        miss++;
        deque<cache> q;
        while(temp>0){
            //cache block;
            //block.tag = atag;
            //block.validBit = 1;
            //block.data = decimal_to_hex_string(address);
            q.push_back(cache(1, atag , decimal_to_hex_string(address)));
            set_associative_cache_FIFO[whichSet] = q;
            temp--;
        }
    }
}      

    //}

//}
    //cout<<"Number of Misses = "<<miss;
    //cout<<"\n";
   
   
   
    

