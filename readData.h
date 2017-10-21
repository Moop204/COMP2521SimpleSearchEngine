//Interfaces of the readData file
#define SIZEOFURL 7
#define MAXWORD 50
#define MAXOUTPUT 30

#include "graph.h"

char** GetCollection(int elements, int length);
int LenCollection(void);
Graph GetGraph(char** urlList);
int wordFrequency(char* word, char* url);
void shiftRight(int *list, int pos, int max);
