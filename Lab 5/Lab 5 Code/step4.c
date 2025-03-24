//Name: Andrew Vattuone
//Date: 2/14/25
//Title: Lab5 – Synchronization using semaphores, locks, and condition variables - Step 4
/*Description:
    Implementation of the consumer-producer problem using semaphores. Producer produces 10 integer messages (0-9) and sends
    them to a buffer, which the consumer reads from and prints out. One message is printed at a time and one message is consumed
    at a time. After creating each producer and consumer thread, the main thread sleeps for 1 second before creating the next
    2 threads. To solve problems with the critical section, a mutex lock is used to make sure that only one producer or consumer 
    can access the critical section at a time, a conditional variable and a while loop is used to make sure that the producer can only access the 
    critical seciton if there's at least one open slot in the buffer to insert messages into, and another conditional variable
    and a while loop makes sure that the consumer can only access the critical seciton if there's at least 1 message inside the buffer that 
    can be removed.
*/

//New shared data: condition variables called "full" and "empty", mutex lock called "lock"
//Variable to keep track of how full the buffer is
//Producer thread

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <stdlib.h>

#define BUFFER_SIZE 10
#define MAX_MESSAGES 10
#define NTHREADS 10

pthread_mutex_t lock; // tracks whether either the producer or consumer is currently using the critical seciton
pthread_cond_t full; // signals if the buffer is full or not full
pthread_cond_t empty; // signals if the buffer is empty or not empty

int buffer[BUFFER_SIZE];

int in = 0; // tracks index where next message should be added in buffer
int out = 0; // tracks index where next message should be consumed in buffer
int count = 0; // tracks total number of messages currently in the buffer

// Function used by producer thread to produce the message and put it in the buffer. Uses mutex locks and a while loop to solve critical section problems.
void *producerThread(void *arg)
{
    int item = (int)(size_t)arg;
    printf("Producer produced: %d\n", item);
    // entry section
    pthread_mutex_lock(&lock); // wait for the consumer to stop consuming (or wait for another producer to stop producing)
    
    // wait for the buffer to have an empty slot
    while (count == BUFFER_SIZE)
    {
        pthread_cond_wait(&empty, &lock);
    }
   
    // critical section
    
    // add the message to the buffer
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;

    // exit section
    pthread_cond_signal(&full); // if a consumer thread is waiting for there to be at least 1 filled slot in the buffer wake it up so it can continue
    pthread_mutex_unlock(&lock); // release the lock so another consumer or producer thread can use critical section
}


// Function used by consumer thread to consume the message and remove it from the buffer (just ignores it doesn't actually remove it). Uses mutex locks and a while loop to solve critical section problems.
void *consumerThread()
{
    // entry section
    pthread_mutex_lock(&lock); // wait for the producer to stop producing (or wait for another consumer to stop consuming)

    // wait for the buffer to have at least one filled slot
    while (count == 0)
    {
        pthread_cond_wait(&full, &lock);
    }
    
    // critical section

    // remove the message from the buffer
    int consumed = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;

    // exit section
    pthread_cond_signal(&empty); // if a producer thread is waiting for there to be at least 1 empty slot in the buffer wake it up so it can continue
    pthread_mutex_unlock(&lock); // release the lock so another producer or consumer thread can use critical section

    printf("Consumer consumed: %d\n", consumed);
}

int main()
{
    pthread_t threads[NTHREADS];

    // initilaize locks and condition
    pthread_mutex_init(&lock, NULL); 
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    // creates MAX_MESSAGES pairs of threads (1 producer and 1 consumer on each iteration), with a proucer thread producing a message for the consumer thread to read and print out
    for (int i = 0; i < MAX_MESSAGES; i++)
    {
        pthread_create(&threads[i], NULL, producerThread, (void *)(size_t)i);
        pthread_create(&threads[i], NULL, consumerThread, NULL);
        usleep(1000000); // wait 1 second before creating next producer-consumer thread pair
    }

    return 0;
}