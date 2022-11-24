# CPP Program to simulate a Generalized Cache behaviour

The cache has these parameters: block size (b), number of the set (S), number of ways (N) and size of the cache (C). The cache must have these fields: Valid-bit, Tag and Data.  The user can choose the following cache organization:

    1. Fully associative cache 
        a. Block size
            i. 1-word
            ii. 2-word
        b. Replacement algorithms
            i. FIFO 
            ii. LRU 
    2. Direct mapped cache
        a. Block size
            i. 1-word
            ii. 2-word
    3. Set associative cache (Marks: 7)
        a. No of ways
            i. Block size
                1. 1-word
                2. 2-word
        b. Replacement algorithms
            i. FIFO
            ii. LRU


To build,, open terminal in the extracted folder and run: 

    make 

    OR

If you don't have 'make' installed:
run this:


    g++ -c cache.cpp
    g++ -c direct_mapped.cpp
    g++ -c fully_associative_lru.cpp
    g++ -c set_associative_lru.cpp
    g++ -c set_associative_fifo.cpp
    g++ -c fully_associative_fifo.cpp
    g++ -o cache cache.o direct_mapped.o fully_associative_lru.o set_associative_lru.o set_associative_fifo.o fully_associative_fifo.o

After doing any one of the above, run the below command to execute the program:

    ./cache
