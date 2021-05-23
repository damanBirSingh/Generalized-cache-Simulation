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
    if(set_ways != 0){
        num_sets = num_lines/set_ways;
        set_associative_cache_FIFO = vector<deque<cache>>(num_sets, deque<cache>(set_ways*block_size, cache(0,0,"")));
    }
}

string decimal_to_hex_string(int decimal_value){
    stringstream ss;
    ss<< std::hex << decimal_value;
    return ss.str();
}

void cache_impl::call_appropriate_cache(int addr){
    switch(c_type){
        case direct_mapped:{
            retrieve_value_from_direct_cache(addr);
            break;
        }
        case fully_associative:{
            if(repl_algo == FIFO)
                retrieve_value_from_fully_associative_cache_LRU(addr);
            else
                retrieve_value_from_fully_associative_cache_LRU(addr);
            break;
        }
        case set_associative:{
            if(repl_algo == FIFO)
                retrieve_value_from_set_associative_cache_FIFO(addr);
            else
                retrieve_value_from_set_associative_cache_LRU(addr);
            break;
        }
    }
}

void cache_impl::print_appropriate_cache_state(){
    cout<<"Line/Set Num   \tvalidBit\tTag\tdata"<<endl;
    switch(c_type){
        case direct_mapped:{
            for(int i=0; i<num_lines; i++){
                if( (direct_cache.find(i) != direct_cache.end()))
                    cout<<i<<"\t\t"<<(direct_cache.find(i)->second).validBit<<"\t\t"<<(direct_cache.find(i)->second).tag<<"\t"<<(direct_cache.find(i)->second).data;
                else 
                    cout<<i;
                cout<<"\n";
            }
            break;
        }
        case fully_associative:{
            if(repl_algo == FIFO){

            }else{
                for(int i=0; i<num_lines; i++){
                    map<int, cache>::iterator it;
                    if( (fully_associative_cache.find(i) != fully_associative_cache.end())){
                        for(cache val: set_associative_cache[i]){
                            cout<<i<<"\t\t"<<val.validBit<<"\t\t"<<val.tag<<"\t"<<val.data<<endl;
                        }
                    } else 
                        cout<<i<<endl;
                }
            }
                
            break;
        }
        case set_associative:{
            if(repl_algo == FIFO){
                for(int i = 0; i<set_associative_cache_FIFO.size(); i++){
                    for(int j=0; j<set_associative_cache_FIFO[i].size(); j++){
                        cout<<i<<"\t\t  ";
                        cout<<set_associative_cache_FIFO[i][j].validBit<<"\t\t";
                        cout<<set_associative_cache_FIFO[i][j].tag<<"\t";
                        cout<<set_associative_cache_FIFO[i][j].data<<"\t";
                        cout<<"\n";
                    }
                }
            }else{
                for(int i=0; i<num_sets; i++){
                    if( (set_associative_cache.find(i) != set_associative_cache.end())){
                        for(cache val: set_associative_cache[i]){
                            cout<<i<<"\t\t"<<val.validBit<<"\t\t"<<val.tag<<"\t"<<val.data<<endl;
                        }
                    } else 
                        cout<<i<<endl;
                }
            }
            break;
        }
    }
}

int main(){
    ::cache_impl ch;
    cout<<"Enter Cache Size(in words), Block Size(in words), space separated\n-->";
    cin>>ch.cache_size>>ch.block_size;
    int temp;
    cout<<"Select Cache type: \n\n1.Direct Mapped\n2.Fully Associative\n3.Set Associative\n-->";
    cin>>temp;
    ch.c_type = (cache_type)temp;
    if(ch.c_type != direct_mapped){
        cout<<"Select Replacement Algorithm\n1.FIFO\n2.LRU\n-->";
        cin>>temp;
        ch.repl_algo = (replacement_algo)temp;
    }
    if(ch.c_type == set_associative){
        cout<<"Enter the number of Ways\n-->";
        cin>>temp;
        ch.set_ways = (cache_type)temp;
    }
    ch.set_cache_parameters(ch.cache_size, ch.block_size, ch.set_ways);
    int i =  0;
    while(i< ch.address.size())
        ch.call_appropriate_cache(ch.address[i++]);
    
    ch.hit = 0; ch.miss=0; //reset after first iteration
    
    for(int j= 1; j<400; j++){
        i=0;
        while(i< ch.address.size())
            ch.call_appropriate_cache(ch.address[i++]);
    }
    ch.print_appropriate_cache_state();
    cout<<"Hits: "<<ch.hit<<" Misses :"<<ch.miss<<endl;

    /*ch.hit = 0; ch.miss=0;
    cout<<"\n\nLRU Set Associative Cache\n";
    ch.set_cache_parameters(16, 1, 2);
    cout<<"Cache Size: 16 words, Block size : 1 word & 2 way set"<<endl;
    i=0;
    while(i< ch.address.size()){
        //cout<<ch.address[i]<<endl;
        ch.retrieve_value_from_set_associative_cache_LRU(ch.address[i++]);
    } 
    ch.hit = 0; ch.miss=0;
    i=0;
    while(i< ch.address.size()){
        //cout<<ch.address[i]<<endl;
        ch.retrieve_value_from_set_associative_cache_LRU(ch.address[i++]);
    }
    cout<<"Set Number\tvalidBit\tTag\tdata"<<endl;
    for(int i=0; i<ch.num_sets; i++){
        if( (ch.set_associative_cache.find(i) != ch.set_associative_cache.end())){
            for(cache val: ch.set_associative_cache[i]){
                cout<<i<<"\t\t"<<val.validBit<<"\t\t"<<val.tag<<"\t"<<val.data<<endl;
            }
        } else 
            cout<<i<<endl;
    }
    cout<<"Hits: "<<ch.hit<<" misses "<<ch.miss<<endl;

    ch.hit = 0; ch.miss=0;
    cout<<"\n\nLRU Fully Associative Cache\n";
    ch.set_cache_parameters(16, 2, 0);
    cout<<"Cache Size: 16 words, Block size : 1 word "<<endl;
    i=0;
    while(i< ch.address.size()){
        //cout<<ch.address[i]<<endl;
        ch.retrieve_value_from_fully_associative_cache_LRU(ch.address[i++]);
    } 
    ch.hit = 0; ch.miss=0;
    i=0;
    while(i< ch.address.size()){
        //cout<<ch.address[i]<<endl;
        ch.retrieve_value_from_fully_associative_cache_LRU(ch.address[i++]);
    }
    
    /*cout<<"Set Number\tvalidBit\tTag\tdata"<<endl;
    for(int i=0; i<ch.num_sets; i++){
        if( (ch.fully_associative_cache.find(i) != ch.fully_associative_cache.end())){
            for(cache val: ch.set_associative_cache[i]){
                cout<<i<<"\t\t"<<val.validBit<<"\t\t"<<val.tag<<"\t"<<val.data<<endl;
            }
        } else 
            cout<<i<<endl;
    }*/
    //cout<<"Hits: "<<ch.hit<<" misses "<<ch.miss<<endl;
}