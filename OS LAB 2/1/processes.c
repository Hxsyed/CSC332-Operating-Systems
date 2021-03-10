// Write a program ​processes.c​, and let the parent process produce two child processes.
// Oneprintsout" I am first child ,my pid is:"PID, and the other prints out"I am second child, my pid is:"PID.
// Guarantee that the parent terminates after the children terminate (Note,you need to wait for two child processes here). 
// Use the getpid() function to retrieve the PID.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

 
int main()
{
    // pid_t data type stands for process identification and it is used to represent process ids
    pid_t child;
    int status;
    child = fork();
    // prints an error while forking
    if (child == -1)
    {
        fprintf(stderr, "Error occured while forking\n");
        return -1;
    }
    // On success, the PID of the child process is returned in the
    // parent, and 0 is returned in the child.
    else if (child == 0)
    {
        printf("I am child one, my pid is: %d\n", getpid());
        exit(0);
    }
    // If fork does not return -1 or 0 then it tells the user that the parent is wating
    else
    {
        printf("Parent is waiting\n");
        waitpid(child, &status, 0);
        printf("Parent is done waiting\n");
    }

    child = fork();
    // prints an error while forking
    if (child == -1)
    {
        fprintf(stderr, "Error occured while forking\n");
        return -1;
    }
    // On success, the PID of the child process is returned in the
    // parent, and 0 is returned in the child.
    else if (child == 0)
    {
        printf("I am child two, my pid is: %d\n", getpid());
        exit(0);
    }
    // If fork does not return -1 or 0 then it tells the user that the parent is wating
    else
    {
        printf("Parent is waiting\n");
        waitpid(child, &status, 0);
        printf("Parent is done waiting\n");
    }

    return 0;
}