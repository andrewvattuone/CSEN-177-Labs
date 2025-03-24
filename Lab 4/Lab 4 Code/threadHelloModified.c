/**************************************************************
*	threadHello.c - simple multi-threaded program.            *
*   compile with: >gcc -lp threadHello.c -o threadHello       *                                              *
**************************************************************/

//Name: Andrew Vattuone
//Date: 1/29/25  
//Title: Lab4 – Developing multi-threaded applications - Step 2
/*Description: 
   Creates 20 threads, with each one runing a function that prints out the thread's index as well as its thread ID. 
   Sometimes prints duplicate indecies. Also sometimes the 20th thread doesn't execute since the main thread terminates
   before it can execute, sometimes it executes its print statement twice after the "main thread done" print statement 
   due to undefined behavior as the thread executes while the process teriminates, and rarely does the 20th thread execute 
   only once after the "main thread done" statement.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS];

int main() {
    static int i;
    // creates NTHREADS and runs the funciton go for each of them
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i); // thread is created and runs the go function using the address of i as an input
    printf("Main thread done.\n");
}

// prints out the current thread index as well as its threadID
void *go(void *arg) {
    printf("Hello from thread %d with thread ID %d \n", *(int *)arg, (int)pthread_self());
    return (NULL);
}