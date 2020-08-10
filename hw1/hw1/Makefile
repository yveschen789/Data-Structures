#
# Makefile for Hookbook
#
# Homework 1 (spring 2019)
#

CC = clang++
CFLAGS = -Wall -Wextra -c
DEPS = Pirate.h ArrayList.h PirateMates.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hookbook: hookbook.o Pirate.o ArrayList.o
	$(CC) -o hookbook hookbook.o Pirate.o ArrayList.o

provide:
	provide comp15 hw1 Pirate.h Pirate.cpp ArrayList.h \
		ArrayList.cpp PirateMates.h Makefile

clean:
	rm -f *.o core* *~ hookbook
