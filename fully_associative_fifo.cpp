#include "cache.hpp"

void removeEntry(deque<cache> &fully_associative_cache_fifo, int block_size, int &ind){
	//cout<<"removing\n";
	for(int i = 0; i <block_size; i++){
		ind = (ind+1)%16;
		fully_associative_cache_fifo.pop_front();
		//cout<<endl<<"index: "<<dec<<ind;
	}
}

void cache_impl::retrieve_value_from_fully_associative_cache_FIFO(int address){

	int offsetBits = log2(block_size*word_size);
	bool found = 0;
	int tag = address >> offsetBits;
	//cout<<tag<<endl;
	//cout<<"BLock size"<<block_size<<endl;
	//fflush(stdout);
	for(int j=0; j<fully_associative_cache_fifo.size(); j++){
		//cout<<"Found"<<endl;
		if(fully_associative_cache_fifo[j].tag == tag){	
			found = 1;
			break;
		}
	}
	if(!found){
		//cout<<"Not Found"<<endl;
		if(fully_associative_cache_fifo.size() == cache_size)
			removeEntry(fully_associative_cache_fifo, block_size, ind);
		for(int i = 0; i < block_size; i++){
			//cout<<"adding"<<endl;
			//fflush(stdout);
			fully_associative_cache_fifo.push_back(cache(1, tag, decimal_to_hex_string(address)));
			address += word_size;
		}
		miss++;
	}

}
