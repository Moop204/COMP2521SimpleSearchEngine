// Completed by Justin Or and Andrew Nguyen
// Implemented with BST where key is a string and value is in a list

int InvertedIndex(){
    char *listOfUrls = GetCollection();
    char *invertedIdx = GetInvertedList(listOfUrls);
    
    FILE *fp = fopen("invertedIndex.txt", "w")
    fwrite(invertedIdx, 1, sizeof(invertedIdx), fp);

    return 0;

}
