/*Sample C program for Lab assignment 1*/

/*
    Name: Andrew Vattuone
    Date: 1/20/25
    Title: Lab 2

    Description: 
    Parent process creates a child process. Each process executes a function that executes a loop that for each iteration
    prints out the current process (Parent or Child process) as well as the current iteration number of the loop. Main funciton takes
    in an argument that represents the number of microseconds to wait after the iteration of each loop, so larger inputs will 
    result in longer wait times for the function to finish.
*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }    
    if (pid){
        // Parent process
        for (i=0;i<100;i++) {
            printf("\t \t \t Parent Process %d \n",i);
            usleep(n);
        }
    }
    else{
        // Child process
        for (i=0;i<100;i++) {
            printf("Child process %d\n",i);
            usleep(n);
        }
    }
    return 0;
}
