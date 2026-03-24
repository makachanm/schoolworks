#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic.h"
#include "sensor.h"

int main(int argc, const char* argv[]) {
	if(argc < 3) {
                printf("not enough args\n");
                return;
        }

        if(strcmp(argv[1], "init") == 0) {
                data_init(argv[2], argv[3]);
        } else if(strcmp(argv[1], "print") == 0) {
                data_print(argv[2]);
        } else if(strcmp(argv[1], "edit") == 0) {
                data_edit(argv[2], argv[3], argv[4], argv[5]);
        } else if(strcmp(argv[1], "aprint") == 0) { 
		data_active_print(argv[2]);
	}

        return 0;
}

