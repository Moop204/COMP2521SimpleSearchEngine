//Interfaces of the readData file
#define SIZEOFURL 7
#define MAXWORD 50
#define MAXOUTPUT 30

#include "graph.h"
#include "invertedIndex.h"

char** GetCollection(char* file, int elements, int length);
int LenCollection(char *filename);
Graph GetGraph(char** urlList);
void shiftRight(int *list, int pos, int max);
int wordFrequency(char* word, char* url);
int wordTotal( char* url);
char *RemoveSpecialCharacters(char* str);
void NormaliseWord(char* word);

