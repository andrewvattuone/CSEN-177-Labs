/*
    Name: Andrew Vattuone
    Date: 1/20/25
    Title: Lab 2

    Description: 
    Creates 7 processes, with each process having exactly 2 children (except for the final processes, which are sort of like leaf nodes in a binary tree).
    The PID, parent PID, and children PIDs of each process are printed out (note that the final children don't have any children so they don't print out any Process IDs)

    Processes tree will have the following hierarchy:
        Main parent is parent of Child 1 and Child 2
        Child 1 is parent of Grandchild 1 and Grandchild 2
        Child 2 is parent of Grandchild 3 and Grandchild 4

        The printing order is:

        Child 1 info
        Grandchild 1 info
        Grandchild 2 info

        Child 2 info
        Grandchild 3 info
        Grandchild 4 info

        Main Parent info

    Note that sometimes the info of a process is printed out in it's child or sibling process instead of itself so that proper printing order is maintained
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <sys/wait.h>   /* wait */

int main(int argc, char *argv[]) 
{
    // variables to store PIDs of children. c1pid stands for Child 1 PID, gc1pid stands for Grandchild 1 PID, and so on
    pid_t  c1pid, c2pid, gc1pid, gc2pid, gc3pid, gc4pid;
    
    c1pid = fork(); // main parent create child 1
    if(c1pid == -1) 
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
    } 
    if(!c1pid) // inside Child 1 Process
    {
        pid_t parent = getppid(); // store Main Parent PID for printing out later
        gc1pid = fork(); // Child 1 create child called Grandchild 1

        if(gc1pid == -1) 
        {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }
        if(!gc1pid)// inside Grandchild 1 process
        {
            printf("\nChild 1: PID: %d Parent PID: %d Children PIDs: ", getppid(), parent); //print out Child 1 info now for proper printing order
            printf("%d, ", getpid()); // print out first child of Child 1 (Grandchild 1) PID now but wait for full info later so that Child 1 children PIDs can be displayed before Grandchild info
            exit(0);
        }
        else // inside Child 1 process
        {
            wait(NULL); // wait for Grandchild 1 to terminate before proceeding 
            gc2pid = fork(); // Child 1 create child called Grandchild 2

            if(gc2pid == -1) 
            {
                fprintf(stderr, "can't fork, error %d\n", errno);
            }
            if(!gc2pid) // inside Grandchild 2 process
            {
                printf("%d\n", getpid()); // prints out the PID of the second child of Child 1 (Grandchild 2)
                // Print out the info of Grandchild 1 and Grandchild 2 processes
                printf("\tGrandchild 1: PID: %d Parent PID: %d\n", gc1pid, getppid()); 
                printf("\tGrandchild 2: PID: %d Parent PID: %d\n\n", getpid(), getppid());
                exit(0);
            }
            wait(NULL); // don't let Child 1 terminate before Grandchild 2
        }
        exit(0);
    }
    else // inside Main Parent process
    { 
        wait(NULL); // wait for Child 1 to finish before proceeding so all of Child 1 and Child 1's childrens' info prints before Child 2 info
        c2pid = fork(); // Main Parent create Child 2

        if(c2pid == -1) 
        {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }    
        if(!c2pid) // inside Child 2 process
        {
            pid_t mainParentPID = getppid(); // store Main Parent PID for printing out later

            gc3pid = fork(); // Child 2 create child called Grandchild 3

            if(gc3pid == -1) 
            {
                fprintf(stderr, "can't fork, error %d\n", errno);
            }
            if(!gc3pid) // inside Grandchild 3 process
            {
                
                printf("Child 2: PID: %d Parent PID: %d Children PIDs: ", getppid(), mainParentPID); //print out Child 2 info now for proper printing order
                printf("%d, ", getpid()); // print out first child of Child 2 (Grandchild 3) PID now but wait for full info later so that Child 2 children PIDs can be displayed before Grandchild info
                exit(0);
            }
            else // inside Child 2 process
            {
                wait(NULL); // wait for Grandchild 3 to terminate before proceeding
                gc4pid = fork(); // Child 2 create child called Grandchild 4
                
                if(gc4pid == -1) 
                {
                    fprintf(stderr, "can't fork, error %d\n", errno);
                }
                if(!gc4pid) // inside Grandchild 4 process
                {
                    printf("%d\n", getpid()); // prints out the PID of the second child of Child 2 (Grandchild 4)
                    // Print out info of Grandchild 3 and Grandchild 4 processes
                    printf("\tGrandchild 3: PID: %d Parent PID: %d\n", gc3pid, getppid());
                    printf("\tGrandchild 4: PID: %d Parent PID: %d\n\n", getpid(), getppid());
                    exit(0);
                }
                wait(NULL); // don't let Child 2 termiante before Grandchild 4
            }
            exit(0);
        }
    }

    c2pid = wait(NULL); // store Child 2 PID
    printf("Main Parent: PID: %d Children PIDs: %d, %d \n\n", getpid(), c1pid, c2pid); // Print out Main Parent PID and child PIDs
    exit(0);
    return 0;
}