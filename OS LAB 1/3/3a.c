
/* Read the next 50 characters from source.txt and replace each character '5' with 'A' 
and write to destination.txt. Write "XYZ" into the file */

 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

 
int main(int argc, char *argv[]){

    char *source = argv[1];
    char *dest = argv[2];
    char buffer[50];
    int start = 0;
    int end = 50;
    // a string containing the char's XYZ including '\0'
    char words[4] = "XYZ";

    // If 3 args are passed then it prompts an error in terminal 
    if (argc > 3){
        printf("Usage: ./outfile [source.txt] [destination.txt] \n");
        return 1;
    }

    // Check if source file exists
    int sourcefile = access(source, F_OK);
    // prompts an error if file could not be accessed
    if (sourcefile != 0)
    {
        printf("Failed to access %s file", source);
        return 0;
    }

    // Check if dest file exists
    int destfile = access(source, F_OK);
    // prompts an error if file could not be accessed
    if (destfile != 0)
    {
        printf("Failed to access %s file", dest);
        return 0;
    }

    int opensource = open(source, O_RDONLY);
    // prompts an error if  the source file could not be opened
    if (opensource == -1)
    {
        printf("Couldnt open in %s", source);
        return 1;
    }

    int opendest = open(dest, O_WRONLY | O_CREAT, 0777);
    // prompts an error if  the destination file could not be opened
    if (opendest == -1)
    {
        printf("Couldnt open in %s", dest);
        return 1;
    }

        // start copying 
            read(opensource, buffer, BUFSIZ);

            // Change the characters 
            for(int i=start; i<=end; i++){

                // When it reaches end of file, break out of loop
                 if(end >= 1277) {
                    printf("Task Completed.\n");
                    exit(0);
                }
                // replacing the character '5' with 'A'
                if(buffer[i] == '5'){
                    buffer[i] = 'A';
                }

                // At every 50 iterations, write to file and append counters
                if(i==end-1){
                    write(opendest, buffer, 50);
                    write(opendest, words, 3);
                    // at the end of 50 chars update start and end to restart
                    start = end;
                    end = end + 50;
                }
            }
    // closing the files
    close(opensource); 
    close(opendest);
}


