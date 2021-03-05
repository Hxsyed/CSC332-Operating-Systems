#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
  int fd1 = open("./destination1.txt", O_WRONLY | O_CREAT, 0777);
  int fd2 = open("./destination2.txt", O_WRONLY | O_CREAT, 0777);

  close(fd1);
  close(fd2);

  return 0;
}
