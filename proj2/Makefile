# Makefile for Gerp
# Name: Yves Chen
# Date: 4/19/19
	
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
DEPS = FSTree.h DirNode.h Index.h Query.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

unitTestMain.o: unitTestMain.cpp Index.o FSTree.o DirNode.o Query.o
testMain.o: testMain.cpp Index.o FSTree.o DirNode.o Query.o
Query.o: Index.h

gerp: testMain.o FSTree.o DirNode.o Index.o Query.o
	$(CXX) -o gerp testMain.o FSTree.o DirNode.o Index.o Query.o

unitTesting: unitTestMain.o FSTree.o DirNode.o Index.o Query.o
	$(CXX) -o unitTesting unitTestMain.o FSTree.o DirNode.o Index.o Query.o

clean:
	rm -f *.o core* *~graphtest