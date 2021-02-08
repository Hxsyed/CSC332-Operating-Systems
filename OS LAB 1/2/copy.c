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
    int source, dest;
    char buffer[BUFSIZ];

    // If 3 args are passed then it prompts an error in terminal 
    if (argc != 3){
        printf("Usage: ./outfile [source.txt] [destination.txt] \n");
        return 1;
    }

    // Check if user can access the source file 
    source = access(filepath, R_OK);

    if(source == 0) {

        // If the file can be accessed then open with read access
        source = open(filepath, O_RDONLY);

        // Create new file with third parameter specifying read access
        // u - owner 
        // g - group
        // o - others

        // r = 4
        // w = 2
        // x = 1

        // 6 gives the user the ability to read and write 
        dest = open(destination, O_RDWR|O_CREAT, 666);

        if(source != -1){
            
            // Read contents into buffer
            size_t val = read(source, buffer, sizeof(buffer));

            // Write to new file 
            write(dest,buffer, val);
            
            // close the files when open with opened files 
            close(source); 
            close(dest);
            printf("Copied %s into %s\n", filepath, destination);

        } 
        // Prompts error is the file cannot be read
        else {
            printf("File read failed");
        }
    }
    // Prompts an error if  the file cannot be accessed
    else {
        printf("File cannot be accessed");
    }

}