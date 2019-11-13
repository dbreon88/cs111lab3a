/*
Lab 3a 
lab3a.c
NAME: Dylan Breon
EMAIL: dbreon@ucla.edu
ID: 905187210
*/


#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include "ext2_fs.h"



int main(int argc, char* argv[]){
  if(argc != 2){ 
    fprintf(stderr, "Error: Incorrect Usage! progam takes one argument for filesystem image.");
    exit(1); //correct error code?
  }
  
  
  char* fileName = argv[1];
  int fileSystem;
  fileSystem = open(fileName, O_RDONLY);
    if(fileSystem < 0){
    char* errorDesc = strerror(errno);
    fprintf(stderr, "Error opening input file %s: %s\n", fileName, errorDesc);
    exit(2);
    }

    //Superblock
  unsigned int inodes_count = 0, blocks_count = 0, inode_size=0, blocksPerGrp = 0, inodesPerGrp = 0, firstUnusedInode = 0;
          struct ext2_super_block super;
    int bytesRead;
    bytesRead = pread(fileSystem, &super, sizeof(super), 1024);
    if(bytesRead<0){
      char* errorDesc = strerror(errno);
    fprintf(stderr, "Error reading from super block: %s\n",  errorDesc);
    exit(1);
    }else if(bytesRead<1024){
      fprintf(stderr, "Error: could not read all of the bytes from the super block.\n");
    exit(1); 
    }
    
    inodes_count = super.s_inodes_count;
    blocks_count = super.s_blocks_count;
    unsigned int block_size = 1024 << super.s_log_block_size;
    inode_size = super.s_inode_size;
    blocksPerGrp = super.s_blocks_per_group;
    inodesPerGrp = super.s_inodes_per_group;
    firstUnusedInode = super.s_first_ino;
    printf("SUPERBLOCK,");
    printf("%u,", blocks_count);
    printf("%u,", inodes_count);
    printf("%u,", block_size);
    printf("%u,", inode_size);
    printf("%u,", blocksPerGrp);
    printf("%u,", inodesPerGrp);
    printf("%u\n", firstUnusedInode);

    //Group summary
    //unsigned int numGroups = blocks_count/blocksPerGrp;
    unsigned int numFreeB=0, numFreeInodes=0, blockMapNum=0, InodeMapNum=0, firstInodesBlockNum=0;
    struct ext2_group_desc group;
 

     bytesRead = pread(fileSystem, &group, sizeof(group), 2048);
    if(bytesRead<0){
      char* errorDesc = strerror(errno);
    fprintf(stderr, "Error reading from group descriptors: %s\n",  errorDesc);
    exit(1);
    }

    numFreeB= group.bg_free_blocks_count;
    numFreeInodes =  group.bg_free_inodes_count;
    blockMapNum = group.bg_block_bitmap;
    InodeMapNum = group.bg_inode_bitmap;
    firstInodesBlockNum = group.bg_inode_table;
    printf("GROUP,0,%u,%u,%u,%u,%u,%u,%u\n", blocks_count, inodesPerGrp, numFreeB,numFreeInodes,blockMapNum,InodeMapNum,firstInodesBlockNum); 

    



    
    
      exit(0);
}//end main
