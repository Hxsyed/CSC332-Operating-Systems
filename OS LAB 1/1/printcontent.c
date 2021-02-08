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
    int returnval;
    char buffer[returnval];

    // Check if it exists
    returnval = access(filepath, R_OK);

    // After checking if the file exists it then read and print to the terminal
    if(returnval == 0){
        // opens the file in read only mode
        returnval = open(filepath, O_RDONLY);
        // read() attemps to read up to count bytes from the file into the buffer. 
        read(returnval, buffer, sizeof(buffer));
        // closes the file when done 
        close(returnval);
        printf("%s\n", buffer);
    } 
    // AFter checking the file, if some errors exist 
    else {
    
    // If the file does not exist 
        if (errno == ENOENT){
            printf("The file %s does not exist\n", filepath);
        }
    // If the file is not accessible to the user
        if (errno == EACCES){
            printf("The file %s is not accessible\n", filepath);
        }
    }

    return 0;
}