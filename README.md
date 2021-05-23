# ACA Assignment, Various Cache implementations

To build, run $make then $./cache
Or if you don't have make installed: 
run this: 

g++ -c cache.cpp
g++ -c direct_mapped.cpp
g++ -c fully_associative_lru.cpp
g++ -c set_associative_lru.cpp
g++ -c set_associative_fifo.cpp
g++ -c fully_associative_fifo.cpp
g++ -o cache cache.o direct_mapped.o fully_associative_lru.o set_associative_lru.o set_associative_fifo.o fully_associative_fifo.o