#
# Filename: Graph.cpp
# Contains: Makefile for homework 5
# Andrew Cervantes
#
CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11
DEPS = Actor.h SixDegrees.h Graph.h Queue.h Stack.h LinkedList.h
all: sixdegrees graphtest 
 %.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

sixdegrees: main.o Actor.o SixDegrees.o Graph.o Queue.o Stack.o LinkedList.o
	$(CC) -o sixdegrees main.o Actor.o SixDegrees.o Graph.o Queue.o Stack.o LinkedList.o

graphtest: test-graph.o Actor.o Graph.o Queue.o Stack.o LinkedList.o
	$(CC) -o graphtest test-graph.o Actor.o Graph.o Queue.o Stack.o LinkedList.o

clean:
	rm -f *.o core* *~ sixdegrees
	rm -f *.o core* *~ graphtest
