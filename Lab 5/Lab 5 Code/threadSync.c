//Name: Andrew Vattuone
//Date: 2/14/25
//Title: Lab5 – Synchronization using semaphores, locks, and condition variables - Step 1
/*Description:
    Creates 10 threads, each with an index 0-9. Each thread runs a function that prints out "Thread (thread index) Entered
    Critical Section", and then sleeps for 1 second before continuing. The main thread waits for all 10 threads to terminate 
    before continuing, and after each thread terminates it prints out "Thread (thread index) termianted." A semaphore is
    used to prevent multiple threads from printing out their "Thread Entered Critical Section" statements at the same time,
    which prevents race conditions that could otherwise cause the incorrect index to be printed.
*/

// Thread Sychronization
//To compile this code:
//If using the SCU Linux lab first add #include<fcntl.h>
//Then you're ready to compile.
//gcc threadSync.c
//gcc threadSync.c -o test

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>


#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *sem; 

void* go(void* arg) { 
  sem_wait(sem); //entry section
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
   sleep(1); 
  sem_post(sem); //exit section 
  return (NULL);
} 

int main() { 
   sem = sem_open("sem", O_CREAT, 0644, 1);
   static int i;
   for (i = 0; i < NTHREADS; i++)  
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
   for (i = 0; i < NTHREADS; i++) {
      pthread_join(threads[i],NULL);
      printf("\t\t\tThread %d returned \n", i);
      }
   printf("Main thread done.\n");
   sem_unlink("sem"); 
   return 0; 
} 
