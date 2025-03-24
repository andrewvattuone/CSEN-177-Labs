//Name: Andrew Vattuone
//Date: 2/14/25
//Title: Lab5 – Synchronization using semaphores, locks, and condition variables - Step 2
/*Description:
    Creates 10 threads, each with an index 0-9. Each thread runs a function that prints out "Thread (thread index) Entered
    Critical Section", and then sleeps for 1 second before continuing. The main thread waits for all 10 threads to terminate 
    before continuing, and after each thread terminates it prints out "Thread (thread index) termianted." A mutex lock is
    used to prevent multiple threads from printing out their "Thread Entered Critical Section" statements at the same time,
    which prevents race conditions that could otherwise cause the incorrect index to be printed.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <stdlib.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock; 

void* go(void* arg) { 
    // only allows one thread at a time to print out its print statement
  pthread_mutex_lock(&lock); //entry section
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
   sleep(1); 
  pthread_mutex_unlock(&lock); //exit section 
  return (NULL);
} 

int main() 
{ 
    pthread_mutex_init(&lock, NULL); // create mutex lock
    static int i;
    
    // creates 10 threads and has each one run the go function
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    
    // waits for all threads to terminate before continuing
    for (i = 0; i < NTHREADS; i++) 
    {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }

    printf("Main thread done.\n");
    pthread_mutex_destroy(&lock); // don't need lock anymore so destroy it

    return 0; 
} 