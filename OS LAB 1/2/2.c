// Create the cp command using open() and write() system calls to copy the conents of source.txt to destination.txt

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){

    char *filepath = argv[1];
    char *destination = argv[2];
    int fd_source, fd_dest;
    char buffer[BUFSIZ];

    // Check if 3 arguments are passed
    if (argc != 3){
        printf("Usage: ./outfile [source.txt] [destination.txt] \n");
        return 1;
    }

    // Check for file 
    fd_source = access(filepath, R_OK);

    if(fd_source == 0) {

        // Open and with read access
        fd_source = open(filepath, O_RDONLY);

        // Create new file with third parameter specifying read access
        // 0666 (owner | group | world) permissions 6=rw
        fd_dest = open(destination, O_RDWR|O_CREAT, 0666);

        if(fd_source != -1){
            
            // Read contents into buffer
            buffer[sizeof(buffer)-1] = '\0';
            ssize_t count = read(fd_source, buffer, sizeof(buffer)-1);

            // Write to new file 
            write(fd_dest,buffer, count);
            
            close(fd_source); close(fd_dest);
            printf("Copied %s into %s\n", filepath, destination);

        } else {
            printf("File read failed");
        }

    } else {
        printf("File access failed");
    }

}