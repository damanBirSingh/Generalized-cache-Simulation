#include<bits/stdc++.h>
#include "cache.hpp"

//using namespace std;

cache_impl::cache_impl(){
    file.open("LW-sAddrs.txt");
    string num;
    while(getline(file, num, ',')){
        address.push_back(stoi(num, nullptr, 16));
    }
}

cache_impl::~cache_impl(){
    file.close();
}

void cache_impl::set_cache_parameters(int cache_size, int block_size, int set_ways){
    this->cache_size = cache_size;
    this->block_size = block_size;
    this->set_ways = set_ways;
    num_lines = cache_size/block_size;
    block_offset_bits = log2(block_size*4);
    if(set_ways != 0)
        num_sets = num_lines/set_ways;
}

string decimal_to_hex_string(int decimal_value){
    stringstream ss;
    ss<< std::hex << decimal_value;
    return ss.str();
}


int main(){
    
    ::cache_impl ch;
    cout<<"Direct Mapped Cache\n"<<endl;
    ch.set_cache_parameters(16, 2, 0);
    cout<<"Cache Size: 16 words and Block size : 1 word"<<endl;
     int i =  0;
    while(i< ch.address.size()){
        ch.retrieve_value_from_direct_cache(ch.address[i++]);
        if(ch.block_size == 2)
            ch.retrieve_value_from_direct_cache(ch.address[i++]);
    } 
    ch.miss = 0;
    
    for(int j= 1; j<400; j++){
        i=0;
        while(i< ch.address.size()){
            ch.retrieve_value_from_direct_cache(ch.address[i++]);
            if(ch.block_size == 2)
                ch.retrieve_value_from_direct_cache(ch.address[i++]);
        } 
    }
    cout<<"Line Number\tvalidBit\tTag\tdata"<<endl;
    for(int i=0; i<ch.num_lines; i++){
        if( (ch.direct_cache.find(i) != ch.direct_cache.end()))
            cout<<i<<"\t\t"<<(ch.direct_cache.find(i)->second).validBit<<"\t\t"<<(ch.direct_cache.find(i)->second).tag<<"\t"<<(ch.direct_cache.find(i)->second).data;
        else 
            cout<<i;
        cout<<"\n";
    }

    cout<<"Hits: "<<ch.hit<<" misses "<<ch.miss<<endl;

    ch.hit = 0; ch.miss=0;
    cout<<"\n\nLRU Set Associative Cache\n";
    ch.set_cache_parameters(16, 1, 2);
    cout<<"Cache Size: 16 words, Block size : 1 word & 2 way set"<<endl;
    i=0;
    while(i< ch.address.size()){
        cout<<ch.address[i]<<endl;
        ch.retrieve_value_from_set_associative_cache(ch.address[i++]);
        if(ch.block_size == 2)
            ch.retrieve_value_from_set_associative_cache(ch.address[i++]);
    } 
    ch.miss = 0;
    i=0;
    while(i< ch.address.size()){
        cout<<ch.address[i]<<endl;
        ch.retrieve_value_from_set_associative_cache(ch.address[i++]);
        if(ch.block_size == 2)
            ch.retrieve_value_from_set_associative_cache(ch.address[i++]);
    } 
    cout<<"Hits: "<<ch.hit<<" misses "<<ch.miss<<endl;
    
}
