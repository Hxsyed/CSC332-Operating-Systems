/*
 * Write a special simple command interpreter that takes command and its arguments.
 * interpreter is a program where the main process creates a child process to execute the
 * command using ​exec()
 * After executing the command, it asks for a new command input (i.e., parent wait for
 * child). The interpreter program will get terminated when the user enters ​ quit​ .
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int child;
	char* args[1024];
	char buffer[1024];
	int count;
	
	while(true){
		char delimiter[2] = " ";
		printf("Terminal:$ ");

        /* 
		 * Reads size0f(buffer)-1 characters from the file stream stdin
         * Stores them in the array buffer
		 */ 
		fgets(buffer, sizeof(buffer), stdin);

        /* strtok: Breaks a string into a series of tokens based on a delimiter
		 * Add each token to the array to populate list of arguments
		 */
		args[count] = strtok(buffer, delimiter);
		while (args[count] != NULL){
			count++;
			args[count] = strtok(NULL, delimiter);
		}

		//remove newline char on final argument
		args[count-1][strlen(args[count- 1 ]) - 1] = '\0';

		// terminates the program when user quits
		if (strcmp(args[0], "quit" ) == 0){
			exit(0);	
		}
		
		// prompts an error when child process could not be forked
		child = fork();
		if (child == -1){
			perror("Failed to fork child process");
			exit(-1);
		}
		else if(child == 0){
			execvp(args[0], args);
			
			printf("Invalid Command\n");
			exit(0);
		}
		
		wait(NULL);
		// Reset for next command
		count = 0;
		printf("\n");
	}
	return 0;
}

