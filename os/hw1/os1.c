#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int code_bytes;
} process;

typedef struct {
    unsigned char op;
    unsigned char len;
} code_tuple;

int main() {
    process* p;
    p = (process *)malloc(sizeof(process));

    while(1) {
        if(!fread(p, sizeof(process), 1, stdin))
            break;

        int code_length = (p->code_bytes / 2);
        
        code_tuple* codes;
        codes = (code_tuple *)malloc(sizeof(process) * code_length);

        for(int i = 0; i < code_length; i++) {
            fread(&codes[i], sizeof(code_tuple), 1, stdin);
        }

        printf("%d %d %d\n", p->pid, p->arrival_time, p->code_bytes);
        for(int i = 0; i < code_length; i++) {
            printf("%d %d\n", codes[i].op, codes[i].len);
        }

        free(codes);
    }

    free(p);

    return 0;
}