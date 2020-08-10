#
#  Makefile for Proj1
#  COMP15
#  Spring 2019
#


CC = clang++
CFLAGS = -std=c++11 -Wall -Wextra -g3
DEPS = Trie.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

SeqMatch: SeqMatch.o Trie.o
	$(CC) -o SeqMatch SeqMatch.o Trie.o

SeqMatch-test: SeqMatch-test.o Trie.o
	$(CC) -o SeqMatch-test SeqMatch-test.o Trie.o

clean:
	rm -f *.o core* *~ SeqMatch