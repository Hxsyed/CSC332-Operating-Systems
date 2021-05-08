#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/wait.h>
#include "sem.h"

int main()
{
  srand(time(NULL));

  // declare semaphores
  int lock = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int papersemaphore = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int tobaccosemaphore = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int matchsemaphore = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

  // initialize semaphores
  sem_create(lock, 1);
  sem_create(agent, 0);
  sem_create(papersemaphore, 0);
  sem_create(tobaccosemaphore, 0);
  sem_create(matchsemaphore, 0);

  // fork the paper process
  int pid1 = fork();
  if (pid1 == 0)
  {
    while (1)
    {
      P(papersemaphore);
      P(lock);

      printf("paper rolled a cigarette\n");

      V(agent);
      V(lock);
    }
  }

  // fork the tobacco process
  int pid2 = fork();
  if (pid2 == 0)
  {
    while (1)
    {
      P(tobaccosemaphore);
      P(lock);

      printf("tobacco rolled a cigarette\n");

      V(agent);
      V(lock);
    }
  }

  // fork the match process
  int pid3 = fork();
  if (pid3 == 0)
  {
    while (1)
    {
      P(matchsemaphore);
      P(lock);

      printf("match rolled a cigarette\n");

      V(agent);
      V(lock);
    }
  }

  // agent process
  if (fork() == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      P(lock);

      // random number to pick smoker
      int random = rand() % 3; 

      // If random == 0 then it wakes up paper semaphore
      if (random == 0)
      {
        printf("Agent woke up paper\n");
        V(papersemaphore);
      }
      // If random == 1 then it wakes up tobacco semaphore
      else if (random == 1)
      {
        printf("Agent woke up tobacco\n");
        V(tobaccosemaphore);
      }
      // If random == 2 then it wakes up match semaphore
      else if (random == 2)
      {
        printf("Agent woke up match\n");
        V(matchsemaphore);
      }
      int remaining = 10 - i;
      printf("Remaining to give: %d\n", remaining);
      printf("—————————————————————————————————————————\n");
      V(lock);
      P(agent);
    }

    printf("Smokers are sleeping and are waiting for their ingredients\n");
    printf("Agent gave the ingredients to the smokers\n");

    P(lock);
    kill(pid1, SIGTERM);
    kill(pid2, SIGTERM);
    kill(pid3, SIGTERM);
    V(lock);

    printf("Agent has canceled all smoker threads\n");
    exit(0);
  }

  wait(NULL);
  exit(0);
}