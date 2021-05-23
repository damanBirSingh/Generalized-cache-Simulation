# README

To build, run

```bash
 make 
```

then run 

$./cache
Or if you don't have make installed:
run this:

```bash
g++ -c cache.cpp
g++ -c direct_mapped.cpp
g++ -c fully_associative_lru.cpp
g++ -c set_associative_lru.cpp
g++ -c set_associative_fifo.cpp
g++ -c fully_associative_fifo.cpp
g++ -o cache cache.o direct_mapped.o fully_associative_lru.o set_associative_lru.o set_associative_fifo.o fully_associative_fifo.o
```

Then run 

```bash
./cache
```