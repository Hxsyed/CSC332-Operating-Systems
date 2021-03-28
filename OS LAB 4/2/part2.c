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


int main(int argc, char* argv[]){

    int fd;
    char buffer[25];
    char* filepath = argv[1];
	FILE* text = NULL;
	char* row;
    int gradesArray[10][10];
	int manager;
	int worker;
    int average;
	int grade;
	int studentRow = 0;
    int column = 0;
	int homeworkCount = 0;
    int sum = 0;
    int maxGrade = 0;
	
	if(argv[1] == NULL){
		printf("./[object_file] [txt_file]\n");
	}

    int exists = access(filepath, F_OK);
  
	if(exists == 0){
        // Open file in read, write and execute mode
		fd = open(filepath,O_RDWR,S_IRWXU);
		if(fd == -1){
			exit(-1);
		} 
		close(fd);
	}
    
    /*
     * Open up the file in read mode
     */ 
    text = fopen(filepath, "r");
    
    /*
     * Reads size0f(buffer)-1 characters from the file text and stores in buffer
     */
    int n = 0;
    while((row = fgets(buffer, sizeof(buffer), text)) != NULL){

        /* sscanf reads a string in the format specified. This string contains whitespace,
         * non-white space, and format specifiers 
         */
    	while(sscanf(row,"%d%n", &grade, &n) == 1){
            
            // Populate a 2D array with each grade
    		gradesArray[studentRow][column] = grade;
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
    	
    	manager = fork();
		if(manager < 0) {
			printf("Manager failed to be forked");
		}
		else if(manager == 0){
            /*
			* Iterate through the students row by the worker
            */
			for(int homework=0; homework<homeworkCount; homework++){

				worker = fork();
				if(worker < 0) {
					printf("Child failed to be forked");
				}
				else if(worker == 0){

                    /*
                    * Let the workers calculate the averages and max grades for each
                    * homework. Iterate through the 2D array for each assignment grade
                    */
					for(int student=0; student<studentRow; student++) {
						sum += gradesArray[student][homework];
                        if(maxGrade < gradesArray[student][homework]){
                            maxGrade = gradesArray[student][homework];
                        }
                        
					}
					average = sum / studentRow;
					printf("[Assignment %d] Average = %d Max = %d\n", homework+1 ,average, maxGrade);

                    // Reset average and start at next column
					average = 0;
					break;
				}
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

