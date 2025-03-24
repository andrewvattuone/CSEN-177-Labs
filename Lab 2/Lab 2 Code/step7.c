/*Sample C program for Lab assignment 7*/

/*
    Name: Andrew Vattuone
    Date: 1/20/25
    Title: Lab 2

    Description:
    Creates a child process that executes the ls command, which prints out the names of all the files in the current 
    directory. The parent process waits for the child to terminate, and afterwards it says the child process was completed.
*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <sys/wait.h>   /* wait */

int main(int argc, char *argv[]) 
{
    pid_t  pid;
    pid = fork();
    if(pid == 0)
    {
        execlp("/bin/ls", "/ls", NULL);
    }
    else
    {
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
}