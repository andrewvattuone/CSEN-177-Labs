//Name: Andrew Vattuone
//Date: 2/14/25
//Title: Lab5 – Synchronization using semaphores, locks, and condition variables - Step 3
/*Description:
    Implementation of the consumer-producer problem using semaphores. Producer produces 10 integer messages (0-9) and sends
    them to a buffer, which the consumer reads from and prints out. One message is printed at a time and one message is consumed
    at a time. After creating each producer and consumer thread, the main thread sleeps for 1 second before creating the next
    2 threads. To solve problems with the critical section, several semaphores are used to make sure that only one producer or
    consumer can access the critical section at a time, that the producer can only access the critical seciton if there's at least
    one open slot in the buffer to insert messages into, and that the consumer can only access the critical seciton if there's 
    at least 1 message inside the buffer that can be removed.  
*/


//Shared data: semaphores called "full", "empty", and "lock"
//Buffer to hold n items
//"lock" provides mutual exclusion to the buffer pool
//"empty" and "full" count the number of empty and full slots in the buffer
//Initially: full = 0, empty = n, lock = 1
//Producer thread

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define BUFFER_SIZE 10
#define MAX_MESSAGES 10
#define NTHREADS 10

sem_t full; // tracks total number of filled slots in the buffer
sem_t empty; // tracks total number of empty stots in the buffer
sem_t lock;  // tracks whether either the producer or consumer is currently using the critical seciton

int buffer[BUFFER_SIZE];

int in = 0; // tracks index where next message should be added in buffer
int out = 0; // tracks index where next message should be consumed in buffer

// Function used by producer thread to produce the message and put it in the buffer. Uses semamphores to solve critical seciton problems.
void *producerThread(void *arg)
{
    int item = (int)(size_t)arg;
    printf("Producer produced: %d\n", item);
    // entry section
    sem_wait(&empty); // wait for at least one empty slot in the buffer
    sem_wait(&lock); // wait for the consumer to stop consuming (or wait for another producer to stop producing)

    // critical seciton

    // add the message to the buffer
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    // exit section
    sem_post(&lock); // release the lock so another consumer or producer thread can use critical section
    sem_post(&full); // increase the number of filled slots tracked by semaphore so consumer knows it has messages it can consume
}

// Function used by consumer thread to consume the message and remove it from the buffer (just ignores it doesn't actually remove it). Uses semamphores to solve critical seciton problems.
void *consumerThread()
{
    // entry section
    sem_wait(&full); // wait for at least 1 filled slot to be in the buffer
    sem_wait(&lock); // wait for the producer to stop producing (or wait for another consumer to stop consuming)

    //critical section

    // remove the message from the buffer
    int consumed = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    // exit section
    sem_post(&lock); // release the lock so another producer or consumer thread can use critical section
    sem_post(&empty); // increase the number of empty slots tracked by semaphore so producer knows it has space to produce another message
    
    // remainder section
    printf("Consumer consumed: %d\n", consumed);
}


int main()
{
    pthread_t threads[NTHREADS];

    sem_init(&full, 0, 0); // set the full semaphore to 0 initially since there are no values in the buffer
    sem_init(&empty, 0, BUFFER_SIZE); // set the empty semaphore to BUFFER_SIZE initially since the buffer is empty and has BUFFER_SIZE available spaces
    sem_init(&lock, 0, 1); // set the lock sempahore to 1 initally since only 1 thread (either consumer or producer) can use the lock at a time

    // creates MAX_MESSAGES pairs of threads (1 producer and 1 consumer on each iteration), with a proucer thread producing a message for the consumer thread to read and print out
    for (int i = 0; i < MAX_MESSAGES; i++)
    {
        pthread_create(&threads[i], NULL, producerThread, (void *)(size_t)i);
        pthread_create(&threads[i], NULL, consumerThread, NULL);
        usleep(1000000); // wait 1 second before creating next producer-consumer thread pair
    }

    return 0;
}

