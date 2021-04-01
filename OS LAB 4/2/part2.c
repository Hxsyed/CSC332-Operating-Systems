/* 
 * Write a program that has a main Director process which reads a file
 * containing grades for all homeworks of all chapters and creates [x]
 * number of manager processes. Each manager processes willl create [y]
 * number of worker processes and pass one homework to each of them
 * and calculate and print the max and average 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char* argv[]){

    char buffer[25];
    char* filepath = argv[1];
	char* row;
    int grades[10][10];
	int studentRow = 0;
    int column = 0;
	int homeworkCount = 0;
	
	// If 2 args are passed then it prompts an error in terminal 
    if (argc > 2){
		// prints error for more arguments
        printf("Usage: ./outfile [source.txt]\n");
        return 1;
    }

    int exists = access(filepath, F_OK);

	 if (exists != 0){
		 // failed to access file
        printf("Failed to access %s file", filepath);
        return 0;
    }
	else{
		int fd = open(filepath,O_RDWR,S_IRWXU);
		// error is -1 is returned 
		if(fd == -1){
			perror("Error opening the file");
		} 
		close(fd);
	}
    
    /*
     * Open up the file in read mode
     */ 
    FILE* text = fopen(filepath, "r");
    
    /*
     * Reads characters from the file text and stores in buffer
     */
    int n = 0;
	int grade;
    while((row = fgets(buffer, sizeof(buffer), text)) != NULL){

    	while(sscanf(row,"%d%n", &grade, &n) == 1){
            
            // Populate a 2D array with each grade
    		grades[studentRow][column] = grade;
    		if(studentRow == 0) 
				homeworkCount++;
    		row += n;
    		column++;
    	}
    	studentRow++; column=0;
    }
    fclose(text);

    
    /*
	* Iterate through the students row by the manager
    */
    for(int i=0; i<studentRow; i++){
    	
    	int manager = fork();
		if(manager < 0) {
			printf("Failed to fork manager");
		}
		else if(manager == 0){
            /*
			* Iterate through the students row by the worker
            */
			for(int homework=0; homework<homeworkCount; homework++){

				int worker = fork();
				// neg value if the child process was uncussessful 
				if(worker < 0) {
					printf("Failed to fork worker");
				}
				// zero value if it created the child process
				else if(worker == 0){
                    // variables to store the sum and max grades
					int sum = 0;

                    // get the sum and max grades
					for(int i=0; i<studentRow; i++) {
						sum += grades[i][homework];
					}
					double average = sum / studentRow;
					printf("Assignment %d - Average = %f \n", homework+1 ,average);
					// reset the average
					average = 0;
					break;
				}
				// returned to parent or caller
				else if(worker > 0) {
					wait(NULL);
                }
			}
			break;
		}
		else if(manager > 0){
			wait(NULL);
			break;
		}
    }
	return 0;
}
