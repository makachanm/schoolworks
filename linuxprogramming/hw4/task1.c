#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int doexit = 0;

void excutena(char** inputs) {
	int pid, stat;
	pid = fork(); 

	if(pid == 0) { 
		execvp(inputs[0], inputs);
	} else { 
		wait(&stat);
	}
}

int evaluatecmd(char* input) { 
	if(strcmp(input, "echo") == 0 || strcmp(input, "sort") == 0 || strcmp(input, "ls") == 0 ||
		strcmp(input, "sleep") == 0 || strcmp(input, "./train") == 0 || strcmp(input, "quit") == 0 ) { 
		return 0;
	} else { 
		return -1;
	}
}

void prompt() { 
	char** args;
	char raw[2048];

	args = (char **)malloc(sizeof(char*) * 128); // maximum arguments = 128
	
	printf("* minishell * ");
	fgets(raw, 2048, stdin);
	raw[strcspn(raw, "\n")] = 0;

	char *ptr;
	int count = 0;
	ptr = strtok(raw, " ");

	while(ptr != NULL) {
		args[count] = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));

		strcpy(args[count], ptr);
		ptr = strtok(NULL, " ");
		count++;
	}
	args[count] = NULL;

	if (count > 0) { 
		if(strcmp(args[0], "quit") == 0) { 
			doexit = 1;		
		}

		if(evaluatecmd(args[0]) == -1) { 
			printf("[ERROR] Unknown Command.\n");
		} else { 
			excutena(args);
		}
	}

	for(int i = 0; i < count; i++) { 
		free(args[i]);
	}

	free(args);
}

int main(int argc, char* argv[]) {
	while(doexit != 1) { 
       		prompt();
	}	
	return 0;
}
