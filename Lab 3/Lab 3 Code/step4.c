//Name: Andrew Vattuone
//Date: 1/22/25  
//Title: Lab3 – Pthreads and inter-process Communication – Pipes - Step 4
/*Description:
    Creates 2 children to execute this command: cat /etc/passwd | grep root. The command searches for any lines containing
    the word "root" in the /etc/passwd file and prints them out. The first child writes the output from cat /etc/passwd 
    (which prints out everything in the /etc/passwd file) into the write end of the pipe, while the second child reads 
    this from the read end of the pipe and passes it into grep root to search for lines containg the word root, and then
    prints out those lines (total of 4 lines)
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main()
{
    int fds[2];
    pipe(fds);

    // Child 1 connects write end of pipe to stdout and then executes cat /etc/passwd so all the contents of /etc/passwd are stored in the write end of the pipe
    if(fork() == 0)
    {
        dup2(fds[1], 1); // connects fds[1] to stdout so that everything that usually goes into stdout goes into write end of pipe
        close(fds[0]); // closes the read end of the pipe to prevent errors
        execlp("cat", "cat", "/etc/passwd", 0); // writes all contents in /etc/passwd to write end of pipe
    }

    // Child 2 reads contents from write end (will contain contents of /etc/passwd) and prints out each line containing "root" using grep
    else if (fork() == 0)
    {
        dup2(fds[0], 0); // connetc fds[0] to stdin so that data can be read from the read end and later passed into grep as if it was being passed using stdin
        close(fds[1]); // closes the write end of the pipe so that child finishes reading data and doesn't wait forever for more write input
        execlp("grep", "grep", "root", 0); // searches /etc/passwd to find all lines with the word "root" and prints them out
    }

    else
    {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }

    return 0;
}