/* Write a C program to implement a command called ​printcontent​ that takes a(text)file name as argument
and display its contents. Report an appropriate message if the file does not exist or can’t 
be opened(i.e.the file doesn’t have read permission).You are to use ​open()​,​read()​,​write()​,and close() ​system calls. */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){

    char *filepath = argv[1];
    int fd;
    char buffer[fd];

    // Check if it exists
    fd = access(filepath, R_OK);

    // Read and print to the terminal
    if(fd == 0){

        //Null terminating so it knows where to end
        buffer[sizeof(buffer)-1] = '\0';

        fd = open(filepath, O_RDONLY);
        read(fd, buffer, sizeof(buffer)-1);
        close(fd);
        printf("%s\n", buffer);
    } 
    else {
        if (errno == ENOENT)
            printf("The file %s does not exist\n", filepath);
        if (errno == EACCES)
            printf("The file %s is not accessible\n", filepath);
    }
    return 0;
}