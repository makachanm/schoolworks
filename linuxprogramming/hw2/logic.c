#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"
#include "sensor.h"

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
                fscanf(data_original, "%04d %10s %s", &datas[i].id, datas[i].name, datas[i].status);
        }

        for(int i = 0; i < SENSOR_COUNT; i++) {
                fwrite(&datas[i], sizeof(sensordata), 1, data_export);
        }

        fclose(data_original);
        fclose(data_export);
}

void data_print(const char* filename) {
        FILE *bfile = fopen(filename, "rb+");
        if(bfile == NULL) {
                printf("cannot read binary file!\n");
                return;
        }

        sensordata datas[SENSOR_COUNT];
        for(int i = 0; i < SENSOR_COUNT; i++) {
                fread(&datas[i], sizeof(sensordata), 1, bfile);
        }

        for(int i = 0; i < SENSOR_COUNT; i++) {
                printf("%04d %10s %s\n", datas[i].id, datas[i].name, datas[i].status);
        }

        fclose(bfile);
}

void data_edit(const char* filename, const char* oid, const char* name, const char* status) {
        FILE *bfile = fopen(filename, "rb+");
        if(bfile == NULL) {
                printf("cannot read binary file!\n");
        }

        sensordata d;
        int target_id = atoi(oid);
        while(1) {
                fread(&d, sizeof(sensordata), 1, bfile);
                if (d.id == target_id) break;
        }
        fseek(bfile, -sizeof(sensordata), SEEK_CUR);

        if(strcmp(name, "-") != 0) strcpy(d.name, name);
        if(strcmp(status, "-") != 0) strcpy(d.status, status);

        fwrite(&d, sizeof(sensordata), 1, bfile);
        fclose(bfile);
}

void data_active_print(const char* filename) { 
	FILE *bfile = fopen(filename, "rb");
	if(bfile == NULL) { 
		printf("cannot read binary file!\n");
	}

	sensordata d;
	for(int i = 0; i < SENSOR_COUNT; i++) { 
		fread(&d, sizeof(sensordata), 1, bfile);
		if(strcmp(d.status, "activate") == 0) { 
			printf("%04d %10s %s\n", d.id, d.name, d.status);
		} else { 
			continue;
		}
	}

	fclose(bfile);
} 
