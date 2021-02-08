
/* Read the next 50 characters from source.txt and replace each character '5' with 'A' 

and write to destination.txt. Write "XYZ" into the file */

 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

 
int main(int argc, char *argv[]){

    char *source = argv[1];
    char *dest = argv[2];
    int sourcefile; // source fd
    int destfile; // dest fd
    char buffer[BUFSIZ];
    int start = 0;
    int end = 50;
    // a string containing the char's XYZ including '\0'
    char words[4] = "XYZ";

    // If 3 args are passed then it prompts an error in terminal 
    if (argc != 3){
        printf("Usage: ./outfile [source.txt] [destination.txt] \n");
        return 1;
    }

    // Check for file 
    sourcefile = access(source, R_OK);

    if(sourcefile == 0) {

        // Open both files
        sourcefile = open(source, O_RDONLY);
        destfile = open(dest, O_RDWR|O_CREAT, 666);

        if(sourcefile != -1){

            // Read from source and populate the buffer
            read(sourcefile, buffer, BUFSIZ);

            // Change the characters 
            for(int i=start; i<=end; i++){

                // When it reaches end of file, break out of loop
                 if(end >= 1277) {
                    break;
                }

                if(buffer[i] == '5'){
                    buffer[i] = 'A';
                }

                // At every 50 iterations, write to file and append counters

                if(i==end-1){
                    write(destfile, buffer, 50);
                    write(destfile, words, 3);
                    start = end;
                    end = end + 50;
                }
            }

            close(sourcefile); close(destfile);

        }
        // prompts an error if file could not be opened
        else {
            printf("Couldnt open in %s", source);
        }
    } 
    // prompts an error if file could not be accessed
    else {
        printf("Failed to access %s file", source);
    }
}