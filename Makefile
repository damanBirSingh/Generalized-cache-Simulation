CXX = g++
CXXFLAGS = 
EXEC = cache
OBJS = cache.o direct_mapped.o fully_associative_lru.o set_associative_lru.o set_associative_fifo.o fully_associative_fifo.o

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJS}

.cpp .o: 
	${CXX} 	${CXXFLAGS} -c $<

cache.o: cache.cpp cache.hpp

direct_mapped.o: direct_mapped.cpp cache.hpp

fully_associative_lru.o: fully_associative_lru.cpp cache.hpp

set_associative_lru.o: set_associative_lru.cpp cache.hpp

set_associative_fifo.o: set_associative_fifo.cpp cache.hpp

fully_associative_fifo.o: fully_associative_fifo.cpp cache.hpp

clean:
	rm -f ${EXEC} ${OBJS}