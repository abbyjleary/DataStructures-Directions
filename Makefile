# Makefile for testing functions submitted with a main function
# It uses catch testing library
# Compile your program: make
# Run your program:  ./a.out
#

#Variables
CFLAGS = -Wall -std=c++11
CC = g++

graph: directions.cc node.h
	$(CC) $(CFLAGS) directions.cc -g -o graph

clean:
	rm -rf graph *.o _TEST/NO_MAIN.cc _TEST/run_tests
