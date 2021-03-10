#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
  // if file already does not exist, then creates it in write and execute mode.
  int fd1 = open("./destination1.txt", O_WRONLY | O_CREAT, 0777);
  int fd2 = open("./destination2.txt", O_WRONLY | O_CREAT, 0777);

  close(fd1);
  close(fd2);

  printf("Sucessfully created destination 1 and 2.txt files with read, write, and execute permissions.\n");

  return 0;
}
