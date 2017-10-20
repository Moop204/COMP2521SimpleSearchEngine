// Completed by Justin and Andrew
// Interface for invertedIndex.c

#define MAXWORD 45

void NormaliseWord(char* word);             // Taken from lab08 of COMP2521
//void RemoveSpecialCharacters(char* word);   // Returns a string without special characters
char *RemoveSpecialCharacters(char *word);

int InvertedIndex(char **urlList);
