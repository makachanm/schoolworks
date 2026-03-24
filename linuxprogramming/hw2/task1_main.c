#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENSOR_COUNT 20

typedef struct _sdata { 
	int id;
	char name[100];
	char status[100];
} sensordata;

void data_init(const char* o_filename, const char* n_filename) { 
	FILE *data_original = fopen(o_filename, "r");
	if(data_original == NULL) { 
		printf("cannot read original file!\n");
		return;
	}
	FILE *data_export = fopen(n_filename, "wb");
	if(data_export == NULL) { 
		printf("cannot open new file!\n");
		return;
	}

	sensordata datas[SENSOR_COUNT];
	for(int i = 0; i < SENSOR_COUNT; i++) { 
		fscanf(data_original, "%d %s %s", &datas[i].id, datas[i].name, datas[i].status); 
	}

	for(int i = 0; i < SENSOR_COUNT; i++) { 
		fwrite(&datas[i], sizeof(sensordata), 1, data_export);
	}

	fclose(data_original);
	fclose(data_export);
}

int main(int argc, const char* argv[]) {
	if(argc < 3) { 
		printf("not enough args\n");
		return;
	}

	if(strcmp(argv[1], "init") == 0) { 
		data_init(argv[2], argv[3]);
	}
	
	return 0;
}
