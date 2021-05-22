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

void cache_impl::set_cache_parameters(int cache_size, int block_size, int num_sets){
    this->cache_size = cache_size;
    this->block_size = block_size;
    this->num_sets = num_sets;
    num_lines = cache_size/block_size;
    block_offset_bits = log2(block_size*4);
}


int main(){
    cout<<"Main"<<endl;
    ::cache_impl ch;
    ch.set_cache_parameters(16, 1, 0);
    
    int i =  0;
    while(i< ch.address.size()){
        ch.retrieve_value_from_cache(ch.address[i++]);
        if(ch.block_size == 2)
            ch.retrieve_value_from_cache(ch.address[i++]);
    } 
    ch.miss = 0;
    
    for(int j= 1; j<10000; j++){
        i=0;
        while(i< ch.address.size()){
            ch.retrieve_value_from_cache(ch.address[i++]);
            if(ch.block_size == 2)
                ch.retrieve_value_from_cache(ch.address[i++]);
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
}