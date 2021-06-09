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
        //cout<<"num sets :"<<num_sets<<endl;
        set_associative_cache_FIFO = vector<deque<cache>>(num_sets, deque<cache>(set_ways*block_size, cache(0,0,"")));
    }
}

string decimal_to_hex_string(int decimal_value){
    stringstream ss;
    ss<< std::hex << decimal_value;
    string hex_string ="";
    for(int i=0; i<4; i++){
        if(decimal_value <= 15)
        hex_string += "0";
        hex_string += ss.str();
    }
    return hex_string+" ";
}

void cache_impl::call_appropriate_cache(int addr){
    switch(c_type){
        case direct_mapped:{
            retrieve_value_from_direct_cache(addr);
            break;
        }
        case fully_associative:{
            if(repl_algo == FIFO)
                retrieve_value_from_fully_associative_cache_FIFO(addr);
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
    
    switch(c_type){
        case direct_mapped:{
            cout<<"Line/Set Num   \tvalidBit\tTag\tdata"<<endl;
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
                //cout<<endl<<"INDEX "<<ind;
	            cout<<endl<<"Tag\tValid\t\tData";
                for(int j = (cache_size - ind); j < fully_associative_cache_fifo.size(); j = j + block_size){
                    cout<<endl<<fully_associative_cache_fifo[j].tag<<"\t"<<fully_associative_cache_fifo[j].validBit<<"\t";
                    int m = j;
                    for(; m < (j + block_size); m++)
                        cout<<" "<<fully_associative_cache_fifo[m].data;
                }
                for(int k = 0; k < (cache_size - ind); k = k + block_size){
                    cout<<endl<<fully_associative_cache_fifo[k].tag<<"\t"<<fully_associative_cache_fifo[k].validBit<<"\t";
                    int m = k;
                    for(; m < (k + block_size); m++)
                    cout<<" "<<fully_associative_cache_fifo[m].data;
                }
                cout<<endl;
            }else{
                cout<<"Line/Set Num   \tvalidBit\tTag\tdata"<<endl;
                int k = 0;
                for(auto val: fully_associative_cache){
                    cout<<k++<<"\t\t"<<val.second.validBit<<"\t\t"<<val.second.tag<<"\t"<<val.second.data<<endl;
                }
            } 
            break;
        }
        case set_associative:{
            cout<<"Line/Set Num   \tvalidBit\tTag\tdata"<<endl;
            if(repl_algo == FIFO){
                for(int i = 0; i<set_associative_cache_FIFO.size(); i++){
                    //int set_size = set_associative_cache_FIFO[i].size()/block_size;
                    for(int j=0; j<set_associative_cache_FIFO[i].size(); j++){
                        cout<<i<<"\t\t  ";
                        cout<<set_associative_cache_FIFO[i][j].validBit<<"\t\t";
                        cout<<set_associative_cache_FIFO[i][j].tag<<"\t";
                        cout<<set_associative_cache_FIFO[i][j].data<<" ";
                        if(block_size == 2 )
                            cout<<set_associative_cache_FIFO[i][++j].data<<"\t";
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
    ch.set_ways = 0;
    if(ch.c_type != direct_mapped){
        cout<<"Select Replacement Algorithm\n1.FIFO\n2.LRU\n-->";
        cin>>temp;
        ch.repl_algo = (replacement_algo)temp;
    }
    if(ch.c_type == set_associative){
        cout<<"Enter the number of Ways\n-->";
        cin>>ch.set_ways;
    }
    ch.set_cache_parameters(ch.cache_size, ch.block_size, ch.set_ways);
    int i =  0;
    ch.ind = 0;
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
    cout<<"Miss Rate: "<<(float)ch.miss/100<<"% "<<endl;
}