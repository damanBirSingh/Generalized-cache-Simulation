#include "cache.hpp"

void add_block_to_fully_associative_cache(map<int, cache> &, list<int> &, int, int, int);
void replace_block_in_fully_associative_cache(map<int, cache> &, list<int> &, int, int, int);

void cache_impl::retrieve_value_from_fully_associative_cache_LRU(int address){
    int mem_tag, mem_block_offset, mem_line;
    //cout<<"address : "<<address<<" bits required : "<<log2(address)<<endl;
    //int tag_bits = ciel(log2(address)) - block_offset_bits;
    //cout<<"Block offset bits: "<<block_offset_bits<<" tag bits "<<tag_bits<<endl;
    mem_block_offset = (address) & (int)(pow(2,block_offset_bits) - 1);
    mem_tag = (address>>block_offset_bits);
    //mem_line = mem_tag%num_lines;
    
    cout<<"Tag: "<<mem_tag<<endl;
    
    if( (fully_associative_cache.find(mem_tag) != fully_associative_cache.end()) ) { 
        hit++;
        auto itr = fa_keys.begin();
        while (itr != fa_keys.end() ) {
            cout << *itr << " ";
            if(*itr == mem_tag)
                break;
            itr++;
        }
        fa_keys.erase(itr);
        fa_keys.push_front(mem_tag);
        //push this block to the front
        cout<<"Is a Hit\n";
    } else {
        cout<<"Is a Miss\n";
        miss++;
        if(fully_associative_cache.size() == num_lines) //cache is full
            replace_block_in_fully_associative_cache(fully_associative_cache, fa_keys,  mem_tag, address, block_size);
        else{
            //cout<<"calling add\n";
            add_block_to_fully_associative_cache(fully_associative_cache, fa_keys,  mem_tag, address, block_size);
        }
            
    }

}

void add_block_to_fully_associative_cache(map<int, cache> &fully_associative_cache, list<int> &keys,  int tag, int address, int block_size){
    //cout<<"adding\n";
    //fflush(stdout);
    //cache block;
    //block.tag = tag;
    //block.validBit = 1;
    string data = decimal_to_hex_string(address);
    if(block_size == 2)
        data += " "+  decimal_to_hex_string(address + 4);
    fully_associative_cache[tag] = cache(1, tag, data);
    keys.push_front(tag);
    
}

void replace_block_in_fully_associative_cache(map<int, cache> &fully_associative_cache, list<int> &keys, int tag, int address, int block_size){
    //cout<<"replacing\n";
    int block_to_remove = keys.back();
    //cout<<"Tag to remove : "<<block_to_remove<<endl;
    keys.pop_back();
    fully_associative_cache.erase(block_to_remove);
    add_block_to_fully_associative_cache(fully_associative_cache, keys, tag, address, block_size);
}