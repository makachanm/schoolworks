#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int doexit = 0;

// Excute Process, N/A
void excutena(char** inputs) {
	int pid, stat;
	pid = fork(); 

	if(pid == 0) { 
		execvp(inputs[0], inputs);
	} else { 
		wait(&stat);
	}
}

// Execute Process, stdout Right Redirect
void excuterdr(char** inputs, int lengths)  { 
	int pid, stat, fd, save;

	char** new_inputs = (char **)malloc(sizeof(char*) * (lengths-1));
	for(int i = 0; i < lengths - 2; i++) { 
		new_inputs[i] = inputs[i];
	}
	new_inputs[lengths - 2] = NULL;

	char* output_file = inputs[lengths - 1];

	fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	save = dup(1);
	dup2(fd, 1);
	close(fd);

	pid = fork();

        if(pid == 0) {
                execvp(new_inputs[0], new_inputs);
        } else {
                wait(&stat);
		dup2(save, 1);
		close(save);
        }
	
	free(new_inputs);

}

// Execute Process, stdin Left Redirect
void excuteldr(char** inputs, int lengths) {
    int pid, stat, fd, save;

    char** new_inputs = (char **)malloc(sizeof(char*) * (lengths-1));
    for(int i = 0; i < lengths - 2; i++) {
	    new_inputs[i] = inputs[i];
    }
    new_inputs[lengths - 2] = NULL;

    char* input_file = inputs[lengths - 1];

    fd = open(input_file, O_RDONLY, 0666);
    
    save = dup(0);
    dup2(fd, 0);
    close(fd);

    pid = fork();

    if(pid == 0) {
        execvp(new_inputs[0], new_inputs);
    } else {
        wait(&stat);
        dup2(save, 0);
        close(save);
    }

    free(new_inputs);

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
			int has_r_rd = -1;
			int has_l_rd = -1;
			for(int i = 0; i < count; i++) { 
				if(strcmp(args[i], ">") == 0) { has_r_rd = i; break; }
				if(strcmp(args[i], "<") == 0) { has_l_rd = i; break; }
			}

			if(has_r_rd != -1) { 
				excuterdr(args, count);
			} else if(has_l_rd != -1) { 
				excuteldr(args, count);			
			} else { 
				excutena(args);
			}
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
