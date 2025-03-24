//Name: Andrew Vattuone
//Date: 3/12/25
//Title: Lab 9 – File Performance Measurement
/*Description:
    Creates several threads, and each one reads 1 byte sizeof(buffer) times from a file at a time, and stores it in a 
    buffer. The number of threads is determined by command line input. Immediately afterward it writes the bytes stored 
    in buffer into a new file. Buffer size is still determined by command line input. Later on the time it takes to do 
    this is calculated using the time terminal command.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h> 

void* threadFunc(void* arg) 
{
    char **argv = (char **)arg;
    int buf_size = atoi(argv[2]); // buffer size determined by command line argument
    char buffer[buf_size]; 
    FILE *fp;
    FILE *fpc;
    fp = fopen(argv[1], "rb");
    fpc = fopen("copy.out", "wb"); // always write to the same output file since we just care about the time it takes to write and don't need to permanently store the data
    size_t bytesRead;
    // reads one block of sizeof(buffer) bytes rom a binary file at a time and stores them in a buffer, and keeps doing this until all bytes have been read
    while (bytesRead = fread(buffer, 1, sizeof(buffer), fp)){
        fwrite(buffer, 1, bytesRead, fpc); // writes all the bytes just read from the first file to a new file
    }
    fclose(fp);
    fclose(fpc);
}

int main(int argc, char *argv[]){
    int num_threads = atoi(argv[3]); // number of threads determined by command line input
    pthread_t threads[num_threads]; 
    int i;

    // creates num_threads threads and has each one read from the file and write to an output file
    for(i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, threadFunc, (void *)argv);
    }

    // waits for all threads to terminate before continuing execution
    for(i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i],NULL);
    }
}