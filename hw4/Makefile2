CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wshadow  -I ..

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c  -o $@ $<

unittests: CXXFLAGS += -isystem /usr/sup/include
unittests: LDLIBS   += -lpthread -lgtest
unittests: LDFLAGS  += -L/usr/sup/lib
unittests: runalltests.o BinarySearchTree-unittest.o ../pretty_print.o \
		../BinarySearchTree.o
	${CXX}  -o $@ $^ ${LDFLAGS} ${LDLIBS}

clean:
	rm -rf unittests *.o *.dSYM && (cd .. && make clean)
