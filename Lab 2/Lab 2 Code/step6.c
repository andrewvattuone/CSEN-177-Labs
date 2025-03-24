/*
    Name: Andrew Vattuone
    Date: 1/20/25
    Title: Lab 2

    Description: 
    Creates 2 threads, called Thread 1 and Thread 2. Each thread executes a function that executes a loop that for each iteration
    prints out the current Thread (Thread 1 or Thread 2) as well as the current iteration number of the loop. Main funciton takes
    in an argument that represents the number of microseconds to wait after the iteration of each loop, so larger inputs will 
    result in longer wait times for the function to finish.
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>
/* main function with command-line arguments to pass */

// function used to run the loop for Thread 1
void* thread1Loop(void * arg) 
{
    int i;
    // prints the number of the current iteration of each iteration of the loop, and says it's part of Thread 1  
    for (i=0;i<100;i++) 
    {
        printf("\t \t \t Thread 1 Loop %d\n", i);
        usleep((size_t)arg); // pauses the function for the inputted number of microseconds
    }
    return 0;
}

// function used to run the loop for Thread 2
void* thread2Loop(void * arg) 
{
    int i;
    // prints the number of the current iteration of each iteration of the loop, and says it's part of Thread 2
    for (i=0;i<100;i++) 
    {
        printf("Thread 2 Loop %d\n",i);
        usleep((size_t)arg); // pauses the function for the inputted number of microseconds
    }
    return 0;
}

int main(int argc, char *argv[]) 
{
    pthread_t thread1;
    pthread_t thread2;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    
    // creates 2 threads and runs thier respective loop functions
    pthread_create(&thread1, NULL, thread1Loop, (void*)(size_t)n);
    pthread_create(&thread2, NULL, thread2Loop, (void*)(size_t)n);  

    // waits for the threads to complete before continuing the main function
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
