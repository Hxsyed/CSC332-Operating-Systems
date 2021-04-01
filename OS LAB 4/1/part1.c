#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

void setScreen();

int main(int argc, char* argv[])
{
	int countArguments;
	char* commandArguments[1024];
	char buffer[1024]; 
	
	while(true)
	{

		countArguments = 0; // Resets 'argc' to 0 

		printf("Terminal:$ "); 

        /* 
         * Stores them in the array buffer
		 */ 
		fgets(buffer,sizeof(buffer),stdin);

        // strtok() function breaks a string intro a sequence of zero or more nonempty tokens. 
		commandArguments[countArguments] = strtok(buffer, " ");
		while (commandArguments[countArguments] != NULL){
			countArguments++;
			commandArguments[countArguments] = strtok(NULL, " ");
		}
		
		//Remove newline char on final argument at the end
		commandArguments[countArguments - 1][strlen(commandArguments[countArguments- 1 ]) - 1] = '\0';

        // quitting the program
		if (strcmp(commandArguments[0], "QUIT" ) == 0){ 
			break; 
		}

		int pid = fork();
		if (pid == -1) //Error-checking
		{
			perror("Fork Failed.");
			exit(-1);
		}
		if (pid == 0)
		{
			// Check for command in directory
			execv(commandArguments[0], commandArguments);
			
			// Checks outside of directory for command
			execvp(commandArguments[0], commandArguments);
			
			// Check if command is not valid
			printf("Invalid command. \n");
			exit(0);
		}
		
		wait(NULL); //Terminate child process
	}
	return 0;
}