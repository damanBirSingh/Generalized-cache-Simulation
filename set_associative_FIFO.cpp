#include<bits/stdc++.h>
using namespace std;

struct cache
    {
       int validBit;
       int tag;
       int data;

        cache(int validBit, int tag, int data)
        : validBit(validBit), tag(tag), data(data) {}
    };

int miss = 0;
int hit = 0;

bool containsTag (deque<cache> qtemp, int atag)
{
    for(int i=0;i<qtemp.size();i++)
    {
        if(atag == qtemp[i].tag)
        return true;
    }
    return false;
}

 void set_Associative_Cache()
{
     int lwAdd[25] = {0x40,0x44,0x48,0x4C,0x70,0x74,0x78,0x7C,0x80,0x84,0x88,0x8C,0x90,0x94,0x98,0x9C,0x0,0x4,0x8,0xC,0x10,0x14,0x18,0x1C,0x20};
     int cacheSize,blockSize,setWay;
     int atag, setBits, offsetBits;
    cout<<"Enter Cache Size in words = ";
    cin>>cacheSize;
    cout<<"\n Enter Block Size in words = ";
    cin>>blockSize;
    cout<<"\nEnter Set way = ";
    cin>>setWay;
    int lines = ( cacheSize / blockSize);
    int NumberOfSet = (lines / setWay);

    offsetBits = log2(blockSize*4);
    setBits = log2(NumberOfSet);
 
    vector<deque<cache>> cacheSet(NumberOfSet, deque<cache>(setWay*blockSize, cache(0,0,0)));
 
    int x = offsetBits + setBits;

    int n = 400;
    int count=0;

while(n--)
{
    for(int i=0;i<25;i++)
    {
         int temp = blockSize;

            int whichSet = ((lwAdd[i])>>offsetBits) & (NumberOfSet-1);
            atag = (lwAdd[i]) >> x;

            if(cacheSet[whichSet][0].validBit == 1)
            {

                if(containsTag(cacheSet[whichSet], atag))
                {
                    hit++;
                }
                else
                {
                    miss++;
                    if(cacheSet[whichSet].size() < (setWay*blockSize))
                    {
                    	while(temp>0)
                    	{
                    		cacheSet[whichSet].push_back(cache(1,atag,lwAdd[i]));
                    		temp--;

                    	}
                    }
                    else
                    {
                    	while(temp > 0)
                    	{
                            cacheSet[whichSet].pop_front();

                           cacheSet[whichSet].push_back(cache(1,atag,lwAdd[i]));
                                temp--;

                    	}
                    }
                }
            }
            else
            {
                cacheSet[whichSet].clear();
                miss++;
                deque<cache> q;
                while(temp>0)
                {
                q.push_back(cache(1, atag , lwAdd[i]));
                cacheSet[whichSet] = q;
                temp--;
                }
            }
          

    }

}
    cout<<"Number of Misses = "<<miss;
    cout<<"\n";
   
   
   
for(int i = 0;i<cacheSet.size();i++)
{
    for(int j=0;j<cacheSet[i].size();j++)
    {
        cout<<"For set = "<<i<<" -> ";
        cout<<cacheSet[i][j].validBit<<"   ";
        cout<<hex<<cacheSet[i][j].data<<"   ";
        cout<<cacheSet[i][j].tag<<"   ";
        cout<<"\n";
    }
}
}

int main()
{
    set_Associative_Cache();
 
    return 0;
}