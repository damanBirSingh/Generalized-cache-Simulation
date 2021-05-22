CXX = g++
CXXFLAGS = 
EXEC = cache
OBJS = cache.o direct_mapped.o fully_associative.o set_associative.o

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJS}

.cpp .o: 
	${CXX} 	${CXXFLAGS} -c $<

cache.o: cache.cpp cache.hpp

direct_mapped.o: direct_mapped.cpp cache.hpp

fully_associative.o: fully_associative.cpp cache.hpp

set_associative.o: set_associative.cpp cache.hpp

clean:
	rm -f ${EXEC} ${OBJS}