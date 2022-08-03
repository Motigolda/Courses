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
        index_block = -1;
    }

    int getfile_size(){
        return file_size;
    }

};

#endif