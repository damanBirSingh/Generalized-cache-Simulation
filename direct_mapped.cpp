#include<bits/stdc++.h>
#include "cache.hpp"

void add_block_to_cache(map<int, struct cache> &, int, int, int, int);

void cache_impl::retrieve_value_from_direct_cache(int mem_addr){
    
    int mem_tag, mem_line, mem_block_offset;

    int line_bits = log2(num_lines);
    int tag_bits = log2(mem_addr) - block_offset_bits + line_bits;
    
    mem_block_offset = (mem_addr) & (int)(pow(2,block_offset_bits) - 1);
    mem_line = (mem_addr>>block_offset_bits) & (int)(pow(2,line_bits) - 1);
    mem_tag = (mem_addr>>(line_bits + block_offset_bits)) & (int)(pow(2,tag_bits) - 1);

    if( (direct_cache.find(mem_line) != direct_cache.end()) && //address wrt line
        ((direct_cache.find(mem_line)->second).tag == mem_tag) ) { // in that line, compare tag
        hit++;
    } else {
        miss++;
        add_block_to_cache(direct_cache, mem_tag, mem_line, mem_addr, block_size);
    }

}

void add_block_to_cache(map<int, struct cache> &direct_cache, int tag, int line, int mem_addr, int block_size){
    cache block;
    block.tag = tag;
    block.validBit = 1;
    block.data = decimal_to_hex_string(mem_addr);
    if(block_size==2)
        block.data += " " + decimal_to_hex_string(mem_addr + 4);
    direct_cache[line] = block;
}