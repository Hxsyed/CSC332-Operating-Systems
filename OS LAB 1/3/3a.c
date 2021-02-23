
/* Read the next 50 characters from source.txt and replace each character '5' with 'A' 
and write to destination.txt. Write "XYZ" into the file */

 
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

 

int main(int argc, char *argv[]){

    char *source = argv[1];
    char *dest = argv[2];

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
    char buf[50], temp;
    int count = 0;
    do
    {
        count = 0;
        for (int i = 0; i < 50; i++){
            if (read(opensource, &temp, 1))
            {
                count++;
                // replacing the character '5' with 'A'
                if (temp == '5')
                    buf[i] = 'A';
                else
                    buf[i] = temp;
            }
            else
            {
                break; // nothing more left to read
            }
        }

        write(opendest, buf, count); // write 50 read characters onto the file
        write(opendest, "XYZ", 3); // Add XYZ after every 50 characters

    } while (count == 50);


    close(opendest);
    close(opendest);

    return 0;

}

