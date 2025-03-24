//Name: Andrew Vattuone
//Date: 3/8/25
//Title: Lab8 – Memory Management
/*Description:
    Generates 10000 random numbers between 0-14, which represents 10000 page requests for pages with page numbers between
    0 and 14. Each number is written to the testInput.txt file and is written on its own line, which makes reading each
    request easier. testInput.txt is used in the first part of the script.sh test to see if the 3 page replacement algorithms
    behave properly
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    int numRequests = 10000; // total of 10000 requests will be made, so 10000 entries in file
    int possiblePages = 15; // page numbers can range from 0-14
    fp = fopen("testInput.txt", "w");
    // generates 10000 random numbers between 0-14 and puts them in testInput.txt, which represents 10000 page requests and is used for testing input
    for (i=0; i<numRequests; i++){ 
        sprintf(buffer, "%d\n", rand()%possiblePages);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}