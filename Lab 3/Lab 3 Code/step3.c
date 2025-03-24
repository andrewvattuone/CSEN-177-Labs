//Name: Andrew Vattuone
//Date: 1/22/25  
//Title: Lab3 – Pthreads and inter-process Communication – Pipes - Step 3
/*Description: 
    Uses 2 children to write the output of the ls command to the write end of the pipe, and then reads from the read end to print 
    out the output of the ls command (a list of all files in the current directory) to the teminal, with each character 
    separated by a space.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc) 
{
    int fds[2];
    char buff[120]; 
    int count;
    int i;
    pipe(fds);

    // Creates child 1 to write the output of the ls command to the write end of the pipe
    if (fork()==0) 
    { 
        printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
        dup2(fds[1], 1); // connects stdout to fds[1] so that everything that normally goes into stdout goes to the write end of the pipe
        close(fds[0]); // closes the read end of the pipe to prevent errors

        execlp("ls", "ls", 0); // executes the ls command

        exit(0);
    }

    // Creates child 2 to read the output of ls from the read end of the pipe and print out the output
    else if(fork()==0) 
    {
        printf("\nReader on the downstream end of the pipe \n");
        close(fds[1]); // closes write end so that data can be read from the read end
        
        while((count=read(fds[0],buff,120))>0) 
        { // reads from the read end of the pipe and stores up to 120 characters into the buffer at a time and stores num of characters read in count
            // writes the input from the read end of the pipe to stdout, with each character separated by a space
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