//Name: Andrew Vattuone
//Date: 3/8/25
//Title: Lab8 – Memory Management
/*Description:
    Reads page requests from an input file and either searches for or adds them to a cache. If a page isn't found in 
    the cache, a FIFO page replacement algorithm is used to select the oldest page added to the cache, select it as a victim,
    and swap it with the newly requested page. Total page faults are recorded and printed out afterward. Size of cache is
    passed in by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// page struct to represent a page in memory
typedef struct {
    int pageno;
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
    }

    int front = 0; // index represents the front of the FIFO queue, with oldest added pages at the front and most recently added pages at the end

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
                break; //break out loop because found page_num in cache
            }
        }
        
        // page wasn't found so select oldest page as the victim page and swap it
        if (foundInCache == false)
        {
            cache[front].pageno = page_num;
            totalFaults++;
            front =(front + 1) % CACHE_SIZE; // new front of queue will be 1 to the right of the old front (cache array is treated as circular)
        }
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;
}