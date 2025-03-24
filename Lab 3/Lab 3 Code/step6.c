//Name: Andrew Vattuone
//Date: 1/22/25  
//Title: Lab3 – Pthreads and inter-process Communication – Pipes - Step 6
/*Description: 
    Creates 10 threads (0-9) and has each one run a function that prints out the thread ID and associated index (0-9). Afterwards
    prints out that the thread has returned (with associated index) and joins the threads together. There's a bug in this program
    where the same index is printed out multiple times for different threads (read observations.txt for more)
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
        pthread_create(&threads[i], NULL, go, &i); // bug is caused here since the address of i is passed into the funciton, but the value of i could change before thread funciton executes
    }
    // joins the 10 threads back together
    for (i = 0; i < NTHREADS; i++) 
    {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }

    printf("Main thread done.\n");
    return 0;
}

// prints out the thread ID of each thread and associated index (this function has a bug where some of the indecies are incorrect or outputted twice, mentioned in observaitons.txt)
void *go(void *arg) 
{
    printf("Hello from thread %ld with iteration %d\n", (long)pthread_self(), *(int *)arg);
    return 0;
}