// Completed by Andrew Nguyen and Justin Or
// Obtains query words from argument
//

#include <stdio.h>
#include <string.h>

char** findMatchedUrls("invertedIndex.txt", queryWords);
char** findPageRank("pagerankList.txt", matched_Url_list);

char** findMatchedUrls(char* invertedIndex, queryWords){
    FILE*  invertedFile = fopen(invertedIndex, "r");
    char*  word;
    char*  url;
    char** listOfUrls;

    int i = 0;

    while(fscanf(invertedIndex, &url, invertedFile ) != EOF){
        FILE* urlFile = fopen(url, "r");
        while(fscanf(url, &word, urlFile) != EOF) {
            if( strcmp(word, queryWords)){
                // Adds to result
                listOfUrls[i] = strdup(word);
                i += 1;
            }
        }
    }
}

char** findPageRank(char* PRList, char** matchedUrlList){
    
}


