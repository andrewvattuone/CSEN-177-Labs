//Name: Andrew Vattuone
//Date: 3/8/25
//Title: Lab8 – Memory Management
/*Description:
    Reads page requests from an input file and either searches for or adds them to a cache. If a page isn't found in 
    the cache, a Second Chance page replacement algorithm is used to find a victim page by selecting a page with its pageHit
    value equal to 0. Since a pageHit value is set to 1 whenever the page is accessed, a page therefore will only be selected
    if the algorithm passes over it twice without the page being accessed by a request, so it's as if each page was given a
    "second chance." The victim page is then swapped out with the newly requested page. Total page faults are recorded and 
    printed out afterward. Size of cache is passed in by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// page struct to represent a page in memory
typedef struct {
    int pageno;
    int pageHit; // records if the page was recently accessed. If it was, it's set to 1, and if it's selected to be a victim for the first time, it's set to 0
} ref_page;


int main(int argc, char *argv[])
{
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    //initialize cache array 
    for (i = 0; i < CACHE_SIZE; i++){ 
         cache[i].pageno = -1;
         cache[i].pageHit = 0;
    }

    int victimChecker = 0;

    // reads all the page requests from stdin
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int

        bool foundInCache = false;
        
        // searches through the cache to find the requested page
        for (i=0; i<CACHE_SIZE; i++)
        {
            if (cache[i].pageno == page_num)
            {
                foundInCache = true;
                cache[i].pageHit = 1; // page was accessesd so change pageHit to 1
                break; //break out loop because found page_num in cache
            }
        }

        // page wasn't found so find a page with its pageHit value set to 0 to be victim and swap with requested page
        if (foundInCache == false)
        {
            bool foundSpot = false;
            // searches the cache for a page to remove
            while(!foundSpot)
            {
                // if pageHit = 1 don't swap the page but set pageHit to 0 so on the next pass it'll swap it
                if(cache[victimChecker].pageHit == 1)
                {
                    cache[victimChecker].pageHit = 0;
                    victimChecker =(victimChecker + 1) % CACHE_SIZE;
                    continue;
                }
                else // select the page as a victim and swap it since it's been selected 2 times before being accessed
                {
                    cache[victimChecker].pageno = page_num;
                    victimChecker =(victimChecker + 1) % CACHE_SIZE; // increase victimChecker to next spot since the current index just had its page swapped
                    foundSpot = true;
                }
            }
            totalFaults++;
        }
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;
}