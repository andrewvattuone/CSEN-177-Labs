//Name: Andrew Vattuone
//Date: 1/22/25  
//Title: Lab3 – Pthreads and inter-process Communication – Pipes - Step 7
/*Description: 
     Creates 10 threads (0-9) and has each one run a function that prints out the thread ID and associated index (0-9). Afterwards
    prints out that the thread has returned (with associated index) and joins the threads together. The bug where the same
    index would be printed out by each thread function was fixed in this version of the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() 
{
    int i;

    // creates 10 threads
    for (i = 0; i < NTHREADS; i++) 
    {
        // fixed bug by directly passing in the value of i, casted to (void*)(size_t), so that the value of i wont change once
        // its passed into the thread function go, so the correct index will be printed out and there will be no repeats
        pthread_create(&threads[i], NULL, go, (void*)(size_t)i); 
    }
    
    // joins all 10 threads back together
    for (i = 0; i < NTHREADS; i++) 
    {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }

    printf("Main thread done.\n");
    return 0;
}

// prints out the thread ID of each thread and associated index (bug where incorrect index or multiple of the same indecies were printed out has been fixed)
void *go(void *arg) 
{
    printf("Hello from thread %ld with iteration %d\n", (long)pthread_self(), arg);
    return 0;
}