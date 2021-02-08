// Extend code snippet 1 to check for read and write access permissions of a given file

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // Takes in first argument file
    char *filepath = argv[1];
    int returnval;

    // Check file existence, will return 0 if true
    returnval = access(filepath, F_OK);

    if (returnval == 0)
        printf("\n %s exists\n", filepath);
    else
    {
        // System call passes error code to errno 
        // ENOENT means no such file or directory

        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }

    // Check read access ...

    // returns an integer value of 0 or -1
    // R_OK checks for read permission  
    returnval = access(filepath, R_OK);

    if(returnval == 0){
        printf("\n %s read access approved\n", filepath);
    }
    else{
        printf("\n %s read access denied\n", filepath);
    }
    

    // Check write access ...

    // returns an integer value of 0 or -1
    // W_OK checks for write permission 
    returnval = access(filepath, W_OK);

    if(returnval == 0){
        printf("\n %s write access approved\n", filepath);
    }
    else{
        printf("\n %s write access denied\n", filepath);
    }
    
    return 0;
}