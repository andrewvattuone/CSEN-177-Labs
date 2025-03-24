//Name: Andrew Vattuone
//Date: 3/12/25
//Title: Lab 9 – File Performance Measurement
/*Description:
    Reads one block of sizeof(buffer) bytes rom a binary file at a time and stores them in a buffer. Keeps reading until 
    all bytes have been read. Buffer size is determined by command line arguments. Later on the time it takes to do this 
    is calculated using the time terminal command.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


int main(int argc, char *argv[]){
    int buf_size = atoi(argv[2]); // buffer size determined by command line argument
    char buffer[buf_size]; 
    FILE *fp;
    fp = fopen(argv[1], "rb");
    // reads one block of sizeof(buffer) bytes rom a binary file at a time and stores them in a buffer, and keeps doing this until all bytes have been read
    while (fread(buffer, sizeof(buffer), 1, fp)){
    }
    fclose(fp);
}