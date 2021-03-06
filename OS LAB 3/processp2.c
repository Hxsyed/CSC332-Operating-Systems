#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
  // open source and file destination files
  int fdSrc = open("./source.txt", O_RDONLY);
  int fdDest1 = open("./destination1.txt", O_WRONLY);
  int fdDest2 = open("./destination2.txt", O_WRONLY);

// prints an error if file couldn't be opened. 
  if (fdSrc == -1 || fdDest1 == -1 || fdDest2 == -1)
  {
    perror("Error");
    return -1;
  }

  char temp[1];
  int count1=0, count2=0;
  do
  {
    // copy the 50 chars from source to dest1
    count1 = 0;
    for (int i = 0; i < 50; i++)
    { 
      if (read(fdSrc, temp, 1))
      { 
        count1++;
        write(fdDest1, temp, 1);
      }
      else
      {
        break;
      }
    }
    if(count1 != 50)
      break;
    // copy the next 100 chars from source to dest2
    count2 = 0;
    for (int i = 0; i < 100; i++)
    { 
      count2++;
      if (read(fdSrc, temp, 1))
      {
        write(fdDest2, temp, 1);
      }
      else
      {
        break;
      }
    }
    if(count2 != 100)
      break;
  } while (1);

  // close the files
  close(fdSrc);
  close(fdDest1);
  close(fdDest2);
  printf("Copy succeesful\n");

  return 0;
}