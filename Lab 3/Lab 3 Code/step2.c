/*Sample C program for Lab assignment 3*/

//Name: Andrew Vattuone
//Date: 1/22/25  
//Title: Lab3 – Pthreads and inter-process Communication – Pipes - Step 2
/*Description: 
    Creates 2 child processes. One process writes the input from the command line (includes command line program execution
    ./step2 as well as any command line arguments) into the write end of the pipe, and prints out the number of arguments
    written to the write end of the pipe. The other process reads from the read end of the pipe and prints out all the 
    contents passed into the write end (which are the command line program execution ./step2 as well as any command line 
    arguments), with each cahracter separated by a space.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc,char *argv[])
{
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);

    // child 1 writes command line arguments into the write end of the pipe
    if (fork()==0) 
    { 
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        close(fds[0]);

        // writes each command line argument from argv into the write end of the pipe
        for(i=0;i<argc;i++) {
            write(fds[1],argv[i],strlen(argv[i]));
        }
    exit(0);
    }
    // child 2 reads the command line arguments inputted into the pipe from the pipe's read end and prints out each command line argument, with each character separated by a space
    else if(fork()==0) 
    {
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]);

        // reads each command line argument from the read end of the pipe and stores it in a buffer
        while((count=read(fds[0],buff,60))>0) 
        {
            // prints out the arguments, with each character separated by a space
            for(i=0;i<count;i++) {
                write(1,buff+i,1);
                write(1," ",1);
            }
            printf("\n");
        }
        exit(0);
    }
    // main parent so close the pipes and wait for the children to end before termianting
    else 
    {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}