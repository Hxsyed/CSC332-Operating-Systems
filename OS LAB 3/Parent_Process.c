#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
  pid_t pd = fork();
  if (pd == 0)
  {
    printf("I am child 1. My pid is %d\n", getpid());
    execl("./Process_P1", "./Process_P1", NULL);
  }
  wait(NULL);

  sleep(3);

  pd = fork();
  if (pd == 0)
  {
    printf("I am child 2. My pid is %d\n", getpid());
    execl("./Process_P2", "./Process_P2", NULL);
  }

  wait(NULL);
  exit(0);
}