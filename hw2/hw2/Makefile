#
#  Makefile
#  COMP15
#  Spring 2019
#
#  Makefile for the train-conductor.cpp, LinkedList and Station
#


CC = clang++
CFLAGS = -Wall -Wextra -c 
DEPS = Station.h LinkedList.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

train-conductor: train-conductor.o Station.o LinkedList.o
	$(CC) -o train-conductor train-conductor.o Station.o LinkedList.o

test: test.o Station.o LinkedList.o
	$(CC) -o test test.o Station.o LinkedList.o

provide:
	provide comp15 hw2 LinkedList.cpp LinkedList.h Makefile \
		Station.cpp Station.h

clean:
	rm -f *.o core* *~ train-conductor
