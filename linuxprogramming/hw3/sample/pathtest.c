#include <stdlib.h>
#include <stdio.h>

int main(){
	char path[100] = "~/251010/hw4/../hw5/./../../250943/";
	char new_path[100];

	realpath(path, new_path);

	printf("*path: %s \n *new_path: %s \n",path, new_path);
	return 0;

}
