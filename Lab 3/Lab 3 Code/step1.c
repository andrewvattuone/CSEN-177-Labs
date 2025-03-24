/*Sample C program for Lab assignment 3*/
//Name: Andrew Vattuone
//Date: 1/22/25  
//Title: Lab3 – Pthreads and inter-process Communication – Pipes - Step 1
/*Description: 
    Creates 2 child processes that effectively execute the ls | more command. Prints out a list of all the 
    files in the current working directory, with each file name on a separate line. 
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//main
int main() 
{
    int fds[2];
    pipe(fds);
    /*child 1 duplicates downstream into stdin */
    if (fork() == 0) 
    {
        dup2(fds[0], 0); // connects read end of pipe with stdin
        close(fds[1]);
        execlp("more", "more", 0); // result from ls will be read from the pipe and passed into the more command and file names are printed out afterwards
    }
    /*child 2 duplicates upstream into stdout */
    else if (fork() == 0) 
    {
        dup2(fds[1], 1); // connects write end of pipe with stdout
        close(fds[0]);
        execlp("ls", "ls", 0); // output from ls will be written to write end of pipe
    }
    else 
    { /*parent closes both ends and waits for children*/
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}