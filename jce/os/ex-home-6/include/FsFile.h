#ifndef FS_FILE_H
#define FS_FILE_H

#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <string>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "FsFile.h"
#include "fsConfig.h"

class FsFile {
    int file_size;
    int block_in_use;
    int index_block;
    int block_size;

    public:
    FsFile(int _block_size) {
        file_size = 0;
        block_in_use = 0;
        block_size = _block_size;
        index_block = NOT_INITIALIZED;
    }

    int getfile_size(){
        return file_size;
    }

    int getFreeSpaceInFileInBytes(){
        return block_size*block_size - file_size;
    }

    int getIndexBlock(){
        return index_block;
    }
    void setIndexBlock(int indexBlock){
        index_block = indexBlock;
    }
    void setBlockSize(int blockSize){
        block_size = blockSize;
    }
    void resetData(){
        file_size = 0;
        block_in_use = 0;
        index_block = NOT_DEFINED;
    }
    void setBlocksInUse(int value){
        block_in_use = value;
    }
    int getBlocksInUse(){
        return block_in_use;
    }
    void setFileSize(int size){
        file_size = size;
    }
    int getFileSize(){
        return file_size;
    }

};

#endif