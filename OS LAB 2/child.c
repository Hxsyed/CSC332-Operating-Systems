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
    pid_t child;
    int status;
    child = fork();
    if (child < 0)
    {
        fprintf(stderr, "Error occured while forking\n");
        return -1;
    }

    else if (child == 0)
    {
        printf("I am child one, my pid is: %d\n", getpid());
        exit(0);
    }

    else
    {
        printf("Parent is waiting\n");
        waitpid(child, &status, 0);
        printf("Parent is done waiting\n");
    }

    child = fork();
    if (child < 0)
    {
        fprintf(stderr, "Error occured while forking\n");
        return -1;
    }

    else if (child == 0)
    {
        printf("I am child two, my pid is: %d\n", getpid());
        exit(0);
    }

    else
    {
        printf("Parent is waiting\n");
        waitpid(child, &status, 0);
        printf("Parent is done waiting\n");
    }

    return 0;

}