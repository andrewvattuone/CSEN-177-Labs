//Name: Andrew Vattuone
//Date: 3/8/25
//Title: Lab8 – Memory Management
/*Description:
    Reads page requests from an input file and either searches for or adds them to a cache. If a page isn't found in 
    the cache, an LRU page replacement algorithm is used to find the least recently used page (the one that hasn't been 
    accessed by a request in the longest period of time), select it as a victim, and swap it with the newly requested 
    page. Total page faults are recorded and printed out afterward. Size of cache is passed in by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// page struct to represent a page in memory
typedef struct {
    int pageno;
    int lastRequested; // stores the number of the last access request made for this page
} ref_page;


int main(int argc, char *argv[])
{
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    //initialize cache array 
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         cache[i].lastRequested = 0;
    }

    int numRequests = 0; // stores the total number of page requests made

    // reads all the page requests from stdin
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        numRequests++; // page request was made so increase numRequests

        bool foundInCache = false;
        int lruRequestNum = numRequests; // stores the request number of the least recently used page in cache
        int lruIndex = 0; // stores the index of the least recently used page in cache

        // searches through the cache to find the requested page and also finds the least recently used page and its index in cache
        for (i=0; i<CACHE_SIZE; i++)
        {
            if (cache[i].pageno == page_num)
            {
                foundInCache = true;
                cache[i].lastRequested = numRequests; // update lastRequested to current request number since the page was just accessed
                break; //break out loop because found page_num in cache
            }
            
            // if a page is found that was requested earlier than the request number in lruRequestNum then update lruRequestNum and lruIndex
            if (lruRequestNum > cache[i].lastRequested)
            {
                lruRequestNum = cache[i].lastRequested; // current page was requested earlier than lruRequestNum so set lruRequestNum to its lastRequested value
                lruIndex = i; // store the index of the new LRU page
            }
        }

        // page wasn't found so select least recently used page as the victim page and swap it
        if (foundInCache == false)
        {
            cache[lruIndex].pageno = page_num;
            totalFaults++;
            cache[lruIndex].lastRequested = numRequests; // new page was loaded in so update its lastRequested value to the current request number
        }
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;



}