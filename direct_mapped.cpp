#include "cache.hpp"

void add_block_to_cache(map<int, cache> &, int, int, int, int);

void cache_impl::retrieve_value_from_direct_cache(int address){
    //cout<<"Cache Size "<<cache_size<<" BLock Size "<<block_size<<endl;
    int mem_tag, mem_line, mem_block_offset;

    int line_bits = log2(num_lines);
    //int tag_bits = log2(address) - block_offset_bits + line_bits;
    
    mem_block_offset = (address) & (int)(pow(2,block_offset_bits) - 1);
    mem_line = (address>>block_offset_bits) & (int)(pow(2,line_bits) - 1);
    mem_tag = (address>>(line_bits + block_offset_bits));
    //cout<<"Line bits:"<<line_bits<<" Block Offset bits "<<block_offset_bits<<endl;
    //cout<<"Line :"<<mem_line<<" Tag "<<mem_tag<<endl;

    if( (direct_cache.find(mem_line) != direct_cache.end()) && //address wrt line
        ((direct_cache.find(mem_line)->second).tag == mem_tag) ) { // in that line, compare tag
        hit++;
        //cout<<"Is a Hit\n";
    } else {
        //cout<<"Is a Miss\n";
        miss++;
        add_block_to_cache(direct_cache, mem_tag, mem_line, address, block_size);
    }

}

void add_block_to_cache(map<int, cache> &direct_cache, int tag, int line, int address, int block_size){
    string data = decimal_to_hex_string(address);
    if(block_size==2)
        data += " " + decimal_to_hex_string(address + 4);
    cache block = cache(1, tag, data);
    direct_cache[line] = block;
}