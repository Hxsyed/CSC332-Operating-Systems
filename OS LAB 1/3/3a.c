/* Read the next 75 characters from source.txt and replace each character '5' with 'O' 
and write to destination.txt. Write "ABC" into the file */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){

    char *source = argv[1];
    char *dest = argv[2];
    int s; // source fd
    int d; // dest fd
    char buffer[BUFSIZ];
    int start = 0; // Initial start for loop
    int end = 76; // 75th character
    char words[] = { 'A', 'B', 'C'};

    // Check for file 
    s = access(source, R_OK);

    if(s == 0) {

        // Open both files
        s = open(source, O_RDONLY);
        d = open(dest, O_RDWR|O_CREAT, 0666);

        if(s != -1){

            // Read from source and populate the buffer
            read(s, buffer, BUFSIZ);

            // Change the characters 
            for(int i=start; i<end; i++){

                if(buffer[i] == '5'){
                    buffer[i] = 'O';
                }

                // At every 75 iterations, write to file and append counters
                if(i==end-1){
                    write(d, buffer, 75);
                    write(d, words, 3);
                    start = end;
                    end = end + 76;
                }
               
                // When it reaches end of file, break out of loop
                 if(end >= 1277) {
                    break;
                }
                
            }

            close(s); close(d);
        } 
        else {
            printf("Couldnt open in %s", source);
        }
       

    } else {
        printf("File access failed");
    }

}