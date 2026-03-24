#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILES 16
#define MAX_BLOCKS 208
#define BLOCK_SIZE 16
#define MAX_FILENAME_LEN 24
#define MAX_FILE_BLOCKS 3

#define MAX_FILENAME_CMD 4

typedef struct {
    int fs_size; // 파일 시스템 전체 크기 (4B)
    int inode_count; // 최대 inode 개수 (4B)
    int block_count; // 최대 데이터 블록 개수 (4B)
    int block_size; // 블록 크기 (바이트) (4B)
    int free_inodes; // 가용 inode 개수 (4B)
    int free_blocks; // 가용 데이터 블록 개수 (4B)
    char inode_alloc_bitmap[MAX_FILES];//사용 중인 inode 관리 배열 (16B)
    char block_alloc_bitmap[MAX_BLOCKS];//사용 중인 데이터블록 관리 배열 (208B)
    char padding[8]; // 남은 공간 패딩 (8B)
} Superblock; 

typedef struct {
    unsigned int size; // 256B
    unsigned char indirect_block; // 1B
    unsigned char blocks[MAX_FILE_BLOCKS]; // 3B
    char file_name[MAX_FILENAME_LEN]; // 24B
} Inode;

typedef struct {
    char data[BLOCK_SIZE]; // 16B
} DataBlock;

typedef struct {
    Superblock superblock; // 256B
    Inode inodes[MAX_FILES]; // 32B * 16 = 512B
    DataBlock blocks[MAX_BLOCKS]; // 16B * 208 = 3328B
} FileSystem;

typedef struct {
    unsigned char command; // 1B
    int filename_length; // 4B
    char* filename; // Modifireable
} fs_command;

FileSystem fs;

void read_fs_information() {
    fread(&fs.superblock, sizeof(Superblock), 1, stdin);
    fread(&fs.inodes, sizeof(Inode), MAX_FILES, stdin);
    fread(&fs.blocks, sizeof(DataBlock), MAX_BLOCKS, stdin);
}

bool has_direct_block(int inodenumber) {
    return (fs.inodes[inodenumber].blocks[0] != 0xff 
        || fs.inodes[inodenumber].blocks[1] != 0xff 
        || fs.inodes[inodenumber].blocks[2] != 0xff);
}

bool has_indirect_block(int inodenumber) {
    return fs.inodes[inodenumber].indirect_block != 0xff;
}

void read_block(unsigned char blknum, bool is_indirect) {
    if(is_indirect) {
        printf("Block [%02d] Indirect: %.*s\n", blknum, BLOCK_SIZE, fs.blocks[blknum].data);
    } else {
        printf("Block [%02d] Direct: %.*s\n", blknum, BLOCK_SIZE, fs.blocks[blknum].data);

    }
}

void read_indirect_block(unsigned char blknum) {
    unsigned char blocks_pointing[BLOCK_SIZE];
    int last_block_pos = 0;

    for(char i = 0 ; i < BLOCK_SIZE / sizeof(char); i++) {
        if(fs.blocks[blknum].data[i] == -1) break;
        blocks_pointing[i] = fs.blocks[blknum].data[i];
        last_block_pos++;
    }

    printf("Block [%02d] Indirect Table: %u", blknum, blocks_pointing[0]);
    for(int i = 1; i < last_block_pos - 1; i++) 
        printf(", %u", blocks_pointing[i]);
    printf(", %u\n", blocks_pointing[last_block_pos - 1]);

    for(int i = 0; i < last_block_pos; i++) {
        read_block(blocks_pointing[i], true);
    }
}

void quite_print_inode(unsigned char inodenum) {
    for(int i = 0; i < MAX_FILE_BLOCKS; i++) {
        if(fs.inodes[inodenum].blocks[i] == -1) break;
        printf("%.*s", BLOCK_SIZE, fs.blocks[fs.inodes[inodenum].blocks[i]].data);
    }

    if(!has_indirect_block(inodenum)) {
        printf("\n\n");
        return;
    }

    unsigned char blocks_pointing[BLOCK_SIZE];
    int last_block_pos = 0;

    for(char i = 0 ; i < BLOCK_SIZE / sizeof(char); i++) {
        if(fs.blocks[fs.inodes[inodenum].indirect_block].data[i] == -1) break;
        blocks_pointing[i] = fs.blocks[fs.inodes[inodenum].indirect_block].data[i];
        last_block_pos++;
    }

    for(int i = 0; i < last_block_pos; i++) {
        printf("%.*s", BLOCK_SIZE, fs.blocks[blocks_pointing[i]].data);
    }
    printf("\n\n");
}

void read_inode(unsigned char inodenum) {
    char* full_str = NULL;

    for(int i = 0; i < MAX_FILE_BLOCKS; i++) {
        if(fs.inodes[inodenum].blocks[i] == 255) break;
        read_block(fs.inodes[inodenum].blocks[i], false);
    }

    if(has_indirect_block(inodenum)) {
        read_indirect_block(fs.inodes[inodenum].indirect_block);
    }

    //print full content
    printf("File Contents: ");
    quite_print_inode(inodenum);
} 

unsigned char find_inode_by_filename(fs_command* cmd) {
    for(unsigned char i = 0; i < MAX_FILES; i++) {
        if(strcmp(fs.inodes[i].file_name, cmd->filename) == 0) return i;
    }

    return 0;
}

void print_indirect_block(unsigned char blknum) {
    unsigned char blocks_pointing[BLOCK_SIZE];
    int last_block_pos = 0;

    for(char i = 0 ; i < BLOCK_SIZE / sizeof(char); i++) {
        if(fs.blocks[blknum].data[i] == -1) break;
        blocks_pointing[i] = fs.blocks[blknum].data[i];
        last_block_pos++;
    }

    printf("\t\tIndirect data blocks: %u", blocks_pointing[0]);
    for(int i = 1; i < last_block_pos - 1; i++) 
        printf(", %u", blocks_pointing[i]);
    printf(", %u\n", blocks_pointing[last_block_pos - 1]);
}

void read_and_do_fs_command() {
    fs_command* f;

    while(1) {
        f = (fs_command *)malloc(sizeof(fs_command));
        
        unsigned char buffer[5];
		if(!fread(buffer, 5, 1, stdin)) {
			break;
		}

        f->command = buffer[0];
        f->filename_length = *((int *)&buffer[1]);

    	int filename_length = f->filename_length;
    	f->filename = (char *)malloc(sizeof(char) * filename_length);
        fread(f->filename, filename_length, 1, stdin);

        if(f->command != 0x01) {
            free(f->filename);
            free(f);
            continue;
        } 

        unsigned char target_inode = find_inode_by_filename(f);
        printf("CMD : READ %s\n", f->filename);

        printf("Inode [%02d]: %s (file size : %u B)\n", 
            target_inode, fs.inodes[target_inode].file_name, fs.inodes[target_inode].size);

        read_inode(target_inode);

        free(f->filename);
        free(f);
    }
}

void print_fs_information() {
    printf("Filesystem Status:\n");
    printf("Superblock Information:\n");
    printf("\tFilesystem Size: %d bytes\n", fs.superblock.fs_size);
    printf("\tBlock Size: %d bytes\n", fs.superblock.block_size);
    printf("\tAvailable Inodes: %d/%d\n", fs.superblock.free_inodes, fs.superblock.inode_count);
    printf("\tAvailable Blocks: %d/%d\n", fs.superblock.free_blocks, fs.superblock.block_count);

    printf("Detailed File Information:\n");

    for(int i = 0; i < MAX_FILES; i++) {
        if(!has_direct_block(i)) continue;

        printf("\tFile: %s\n", fs.inodes[i].file_name);
        printf("\t\tSize: %d\n", fs.inodes[i].size);
        printf("\t\tInode: %d\n", i);

        printf("\t\tDirect blocks: %u", fs.inodes[i].blocks[0]);
        for(int j = 1; j < MAX_FILE_BLOCKS; j++) {
            if(fs.inodes[i].blocks[j + 1] == 0xff || j + 1 >= MAX_FILE_BLOCKS) {
                printf(", %u\n", fs.inodes[i].blocks[j]);
                break;
            } else {
                printf(", %u", fs.inodes[i].blocks[j]);
            }
        }

        if(has_indirect_block(i)) {
            printf("\t\tIndirect block: %u\n", fs.inodes[i].indirect_block);
            print_indirect_block(fs.inodes[i].indirect_block);
        }
    }
}

int main() {
    read_fs_information();
    read_and_do_fs_command();
    print_fs_information();
    return 0;
}