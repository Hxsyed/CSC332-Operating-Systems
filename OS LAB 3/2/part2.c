#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  // The pid_t data type is a signed integer type which is capable of representing a process ID. 
  pid_t pid = fork();

  if (pid == 0)
  {
    printf("Child created! My pid is %d\n", getpid());
    // By default la is an alias for ls -A.
    char *commands[] = {"ls", "-la", NULL};
    execvp(commands[0], commands);
  }

  wait(NULL);
  exit(0);
}