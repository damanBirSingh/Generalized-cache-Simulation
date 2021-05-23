#include "cache.hpp"

#define LEN 10
struct cacheMemory
{
	int tag;
	int data;
	bool valid;
}cacheWord;
int ind;
list<int> addresses;
deque<cacheMemory> cache;
int blockSize, replacementAlgo,cacheSize;
int offsetBits = 0;
int  wordSize = 4;
int misses = 0;

void removeEntry(){
	//cout<<"\n REMOVING ENTRY";
	for(int i = 0; i <blockSize; i++)
	{
		//cout<<"\n REMOVING ENTRY";
		ind = (ind+1)%16;
		cache.pop_front();
		cout<<endl<<"index: "<<dec<<ind;
	}
}

void firstIteration()
{
	bool found;
	list<int>::iterator l;
	int addr;
	for(int n = 0; n < 10; n++)
	{
	for(l = addresses.begin(); l!=addresses.end();++l)
	{	//cout<<hex<<"\nAddr: "<<*l<<" ";
		addr = *l;
		found = 0;
		int tag = addr >> offsetBits;

		for(int j=0; j<cache.size(); j++)
		{
			if(cache[j].tag == tag)
			{	found = 1;
				//cout<<"\n Word found: "<<hex<<*l;
				//cout<<endl<<hex<<cache[j].tag<<"\t"<<cache[j].valid<<"\t"<<hex<<cache[j].data;
			}
		}

		if(!found)
		{
			if(cache.size() == cacheSize)
				removeEntry();
			for(int i = 0; i < blockSize; i++)
			{
			cacheWord.tag = (*l>>offsetBits);
			cacheWord.valid = 1;
			//string d = to_string(*l);
			//cacheWord.data = d+d+d+d;
			stringstream ss;
			string d;
			ss<<hex<<*l;
			ss>>d;
			//cout<<"\n d: "<<d;
			//stoi(d+d+d+d, 0, 16);
			cacheWord.data = *l;//stoi(d+d+d+d, 0, 10);//d+d+d+d;
			addr += wordSize;
			//uint8_t z  = *l;
			//cout<<endl<<hex<<addr<<" Check \t"<<cacheWord.tag<<"\t"<<cacheWord.valid<<"\t"<<hex<<cacheWord.data;//z<<z<<z<<z;//<<cacheWord.data<<cacheWord.data<<cacheWord.data;

			//addToQueue(cacheEntry);
			cache.push_back(cacheWord);


			}
			if(n!=0)
				misses++;

			//if()

		}

		//cout<<endl<<hex<


	}
	}

	cout<<"********CACHE***********";
	cout<<endl<<"INDEX "<<ind;
	cout<<endl<<"Tag\tValid\tData";
	for(int j = (cacheSize - ind); j < cache.size(); j++)
		cout<<endl<<hex<<cache[j].tag<<"\t"<<cache[j].valid<<"\t"<<hex<<cache[j].data<<cache[j].data<<cache[j].data<<cache[j].data;
	for(int k = 0; k < (cacheSize - ind); k++)
		cout<<endl<<hex<<cache[k].tag<<"\t"<<cache[k].valid<<"\t"<<hex<<cache[k].data<<cache[k].data<<cache[k].data<<cache[k].data;
	/*for(int l = 0; l < cacheSize; l++)
			cout<<endl<<cache[l].tag<<"\t"<<cache[l].valid<<"\t"<<hex<<cache[l].data;
*/

}


int main()
{
	ind = 0;
	ifstream inputfile;
	cout<<"Enter block size in words:";
	cin>>blockSize;
	cout<<"Enter replacement algorithm:\n 1.FIFO \n 2.LRU";
	cin>>replacementAlgo;
	cout<<"Enter cache size in words";
	cin>>cacheSize;

	inputfile.open("LW-sAddrs.txt", ios::in);
	char comma[LEN];

	offsetBits = log2(blockSize*wordSize);
	cout<<"\n offset: "<<offsetBits;
	int address;
	hex(inputfile);
	if(inputfile.is_open())
	{
		while(!inputfile.eof())
		{

			//getline(inputfile, address,',');
			inputfile>>address;
			inputfile.getline(comma,LEN,',');
			addresses.push_back(address);

		}
	}
	else
	{
		cout<<"\n Error while opening file";
	}


	list<int>::iterator l;
	int addr;
	bool found = 0;
	for(l = addresses.begin(); l != addresses.end(); ++l)
	{
		cout<<endl<<*l;
	}

	firstIteration();

	cout<<"\nMisses: "<<dec<<misses;
	/*for(int i = 0; i < 10; i++)
	{
		for(l = addresses.begin(); l != addresses.end(); ++l)
		{
			found = 0;
			addr = *l;
			int tag = (addr>>offsetBits);
			for(int j = 0; j < cache.size();j++)
			{
				if(tag == cache[j].tag)
					found = 1;
			}



		}
	}*/

return 0;

}



