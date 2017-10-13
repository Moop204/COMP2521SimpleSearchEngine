// Completed by Andrew Phuoc Nguyen and Justin Chun-Sang Or
// Ranks pages


int PageRankW(int d, int diffPR, int maxIterations){
    
    char *urlList = GetCollection();
    int sizeUrl = sizeof(listOfUrls[0]);
    Graph g = GetGraph(listOfUrls);
    
    int noUrls;

    for(int i = 0; i < noUrls; i++){
        urlList[i] = 1/noUrls;
    }

    int noIter = 0;
    int diff = diffPR;

    while(noIter < maxIterations && diff >= diffPR){
        noIter++;
        int weightIn, weightOut;
        double PR;
        double sum;

        for(
        

        PR = (1-d)/noUrls;  

    }
    // Calculate Page Rank
    // Type? listUrlPageRank = calculatePageRank(g, d, diffPR, maxIterations);
    char *orderedListUrlsPageRank = order(listUrlPageRank);
    int size = strlen(orderedListUrlsPageRank);
    FILE *fp;
    fp = fopen("pagerankList.txt","w");
    fwrite(orderedListUrlsPageRank,1,  sizeof(orderedListUrlsPageRank), fp); 

}
