// Write a C program where ​open ​system call creates a new file (say, ​destination.txt​) and then opens it.
//(Hint: use the bitwise OR flag)

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Track return values
    int returnval;

    // checking if Arguments not passed correctly
    if (2 != argc)
    {
        printf("\n Usage: \n");
        return 1;
    }

    // Set default error code
    errno = 0;
    // Check if available else create new file
    returnval = open(argv[1], O_RDONLY|O_CREAT);

    // Open failed, notify to user
    if (-1 == returnval)
    {
        printf("\n open() failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else
    {
        printf("\n Open() Successful\n");
        /* open() succeeded, now one can do read operations on the    
        file opened since we opened it in read-only mode. Also once done    
        with processing, the file needs to be closed.*/   
        close(returnval);
    }                                     
     return 0;
}
