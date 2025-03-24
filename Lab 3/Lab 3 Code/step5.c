//Name: Andrew Vattuone
//Date: 1/22/25  
//Title: Lab3 – Pthreads and inter-process Communication – Pipes - Step 5
/*Description: 
    Implements the producer-consumer problem, where the prodcer sends a message to the reciever by writing it to the write
    end of the pipe and the consumer recieves the message by reading it from the read end of the pipe. A total of 15 integer messages
    are sent (0-14). The pipe acts as the buffer in this implementation of the problem (note that the array called buffer 
    is just used to store data read from the pipe, and isn't actually shared by the two processes or used for communication,
    as the pipe does that which is why the pipe acts as the "common buffer" in this implementation).
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 15
#define MAX_MESSAGES 15

int main() 
{
    int fds[2];
    pipe(fds);
    
    // create child to act as consumer and read messages passed from producer
    if(fork() == 0)
    {
        close(fds[1]);
        int buffer[BUFFER_SIZE]; // stores data read from read end of pipe
        int i = 0; // index of each message (message 0, message 1, etc)
        
        while(read(fds[0], buffer, sizeof(buffer)) > 0) // reads each message from the read end of the pipe and stores it in the buffer
        {
            printf("Consumer recieved message from producer: Message %d [%d]\n", buffer[0], i++); // prints out the message sent from the producer and its associated index
        }
        exit(0);
    }

    // main parent acts as the producer, sending messages to the consumer
    else
    {
        close(fds[0]);
        int message = 1; // integer message written to the write end of the pipe to be sent to the consumer
        int i = 0; // index of each message (message 0, message 1, etc)

        // create 15 integer messages and write them to the write end of the pipe to be sent to the consumer
        while(i < MAX_MESSAGES) 
        {
            write(fds[1], &message, sizeof(message)); // writes the message to the write end of pipe
            printf("Producer sent message to consumer: Message %d [%d]\n", message++, i++); // prints out the message number and its corresponding index
            usleep(1000000); // waits 1 second before sending the next message
        }
        
        // closes write pipe once finished sending messages and waits for consumer child to end before ending
        close(fds[1]);
        wait(0);
    }

    return 0;
}