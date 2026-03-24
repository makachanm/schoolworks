#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FILES 16
#define MAX_BLOCKS 208
#define BLOCK_SIZE 16
#define MAX_FILENAME_LEN 24
#define MAX_FILE_BLOCKS 3

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

FileSystem fs;

void read_fs_information() {
    fread(&fs.superblock, sizeof(Superblock), 1, stdin);
    fread(&fs.inodes, sizeof(Inode), MAX_FILES, stdin);
    fread(&fs.blocks, sizeof(DataBlock), MAX_BLOCKS, stdin);
}

void read_block(unsigned char blknum) {

}

void read_indirect_block(unsigned char blknum) {
    unsigned char blocks_pointing[BLOCK_SIZE];
    int last_block_pos = 0;

    for(char i = 0 ; i < BLOCK_SIZE / sizeof(char); i++) {
        if(fs.blocks[blknum].data[i] == 0xff) break;
        blocks_pointing[i] = fs.blocks[blknum].data[i];
        last_block_pos++;
    }
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


bool has_direct_block(int inodenumber) {
    return (fs.inodes[inodenumber].blocks[0] != 0xff 
        || fs.inodes[inodenumber].blocks[1] != 0xff 
        || fs.inodes[inodenumber].blocks[2] != 0xff);
}

bool has_indirect_block(int inodenumber) {
    return fs.inodes[inodenumber].indirect_block != 0xff;
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
    print_fs_information();
    return 0;
}