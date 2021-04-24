#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *smoker(void *arg);
void *agent();

pthread_t agentthread, paperthread, tobaccothread, matchthread;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t agentmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t papermutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tobaccomutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t matchmutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
  srand(time(NULL));

  // variables used to determine turn of smoker
  char *paperid = "0";
  char *tobaccoid = "1";
  char *matchid = "2";

  // Initialize  agennt, paper, tobacco and match mutexes
  pthread_mutex_lock(&agentmutex);
  pthread_mutex_lock(&papermutex);
  pthread_mutex_lock(&tobaccomutex);
  pthread_mutex_lock(&matchmutex);

  // create the p-threads
  pthread_create(&agentthread, NULL, agent, NULL);
  pthread_create(&paperthread, NULL, smoker, (void *)paperid);
  pthread_create(&tobaccothread, NULL, smoker, (void *)tobaccoid);
  pthread_create(&matchthread, NULL, smoker, (void *)matchid);

  // wait for agent thread to finish
  pthread_join(agentthread, NULL);

  exit(0);
}

void *smoker(void *arg)
{
  const char *turn = (char *)arg;
  int id = atoi(turn);

  while (1)
  {
    // Put smoker to sleep according to turn
    if (id == 0)
    {
      pthread_mutex_lock(&papermutex);
    }
    else if (id == 1)
    {
      pthread_mutex_lock(&tobaccomutex);
    }
    else if (id == 2)
    {
      pthread_mutex_lock(&matchmutex);
    }

    pthread_mutex_lock(&lock);

    // roll cigarette according to turn
    if (id == 0)
    {
      printf("paper thread rolled a cigarette\n");
    }
    else if (id == 1)
    {
      printf("tobacco thread rolled a cigarette\n");
    }
    else if (id == 2)
    {
      printf("match thread rolled a cigarette\n");
    }

    pthread_mutex_unlock(&agentmutex);
    pthread_mutex_unlock(&lock);
  }
}

void *agent()
{
  for (int i = 0; i < 20; i++)
  {
    pthread_mutex_lock(&lock);

    // random number to pick smoker
    int random = rand() % 3; 

    // If random == 0 then it wakes up paper mutex
    if (random == 0)
    {
      printf("paper thread woke up\n");
      pthread_mutex_unlock(&papermutex);
    }
    // If random == 1 then it wakes up tobacco mutex
    else if (random == 1)
    {
      printf("tobacco thread woke up\n");
      pthread_mutex_unlock(&tobaccomutex);
    }paper
     // If random == 2 then it wakes up match mutex
    else if (random == 2)
    {
      printf("match thread woke up\n");
      pthread_mutex_unlock(&matchmutex);
    }
    int remaining = 20 - i;
    printf("Remaining to give: %d\n", remaining);
    printf("------------------------------------\n");
    pthread_mutex_unlock(&lock);
    pthread_mutex_lock(&agentmutex);
  }

  printf("Smokers are waiting for ingredients\n");
  printf("Agent gave the ingredients to smokers\n");

  pthread_mutex_lock(&lock);
  pthread_cancel(paperthread);
  pthread_cancel(tobaccothread);
  pthread_cancel(matchthread);
  pthread_mutex_unlock(&lock);

  printf("Agent canceled all smoker threads\n");
}