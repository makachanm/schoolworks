#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

char WD[2048];

char type(mode_t mode) { 
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
    
    return('?'); 
}

char* perm_to_string(mode_t mode) {
    static char perms[10];

    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {

        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3 + 0] = 'r';

        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';

        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }

    return(perms);
}

void ls(char* argument) {
	DIR* workdir;
       	workdir = opendir(WD);

	struct dirent* d;

	if(workdir == NULL) { 
		printf("Error: invalid work directory\n");
		return;
	}	

	if(strcmp(argument, "") == 0) { 
		while((d = readdir(workdir)) != NULL) {
		       	if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) continue;	
			printf("%s\n", d->d_name);
		}	
	} else if(strcmp(argument, "-d\n") == 0) { 
		struct stat buf;
		
		while((d = readdir(workdir)) != NULL) {
                        if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) continue;
               		
		       	char real_path[2048];
			sprintf(real_path, "%s/%s", WD, d->d_name);	
			if(lstat(real_path, &buf) == 0) { 
				if(S_ISDIR(buf.st_mode)) printf("%s\n", d->d_name);
			}
		}

	} else if(strcmp(argument, "-a\n") == 0) { 
		struct stat buf;

                while((d = readdir(workdir)) != NULL) {
                        if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) continue;

                        char real_path[2048];
                        sprintf(real_path, "%s/%s", WD, d->d_name);
                        if(lstat(real_path, &buf) == 0) {
                        	printf("%lu %c %s %s\n", buf.st_ino, type(buf.st_mode), perm_to_string(buf.st_mode), d->d_name);
			}
                }	
	} else { 
		printf("Error: not defined command\n");
	}
}

void cd(char* argument) {
	char new_path[2048];
	char trim_path[2048];
	for (int i = 0; argument[i] != 0; i++) {
        	if (argument[i] == '\n') {
        		argument[i] = 0;
        		break;
       		}
    	}

	sprintf(new_path, "%s/%s", WD, argument);

	realpath(new_path, trim_path);
	strcpy(WD, trim_path);	
}

void prompt() { 
	while(1) {
		printf("202412999 explorer ");
	       	printf("%s > ", WD);	
		char raw_command[1024];
		fgets(raw_command, 1024, stdin);

		if(strstr(raw_command, "ls") != NULL) {
			char* args = strtok(raw_command, " ");
			args = strtok(NULL, " ");
			if(args != NULL) { 
				ls(args);
			} else { 
				ls("");
			}
		} else if(strstr(raw_command, "cd") != NULL) {
                        char* args = strtok(raw_command, " ");
                        args = strtok(NULL, " ");
                        if(args != NULL) {
                                cd(args);
                        } else {
                                cd("");
			}
                } else if(strstr(raw_command, "quit") != NULL) { 
			break;
		}
	}
}

int main(int argc, char* argv[]) {
       	strcpy(WD, argv[1]);	
	//printf("%s\n", WD);
	prompt();

	return 0;
}
