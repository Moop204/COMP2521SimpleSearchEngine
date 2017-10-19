# Makefile for Simple Search Engine
# COMP2521 17s2 Ass2
# Completed by Andrew Nguyen & Justin Or

CC = gcc
CFLAGS = -Wall -Werror -DDBUG=1

test : test.o readData.o invertedIndex.o queue.o set.o graph.o pageRank.o
test.o : test.c readData.h invertedIndex.h pageRank.h
readData.o : readData.c readData.h invertedIndex.h set.h queue.h graph.h
invertedIndex.o : invertedIndex.c invertedIndex.h readData.h queue.h set.h
pageRank.o : pageRank.c pageRank.h readData.h invertedIndex.h pageRank.h set.h queue.h graph.h
queue.o : queue.c queue.h
set.o : set.c set.h
graph.o : graph.c graph.h

clean:
	rm -f test.o readData.o invertedIndex.o queue.o set.o graph.o
