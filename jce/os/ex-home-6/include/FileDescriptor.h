#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <string>
#include <cstring>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "FsFile.h"


using namespace std;

class FileDescriptor {
    string file_name;
    FsFile* fs_file;
    bool inUse;

    public:

    FileDescriptor(string FileName, FsFile* fsi) {
        file_name = FileName;
        fs_file = fsi;
        inUse = false;
    }
    ~FileDescriptor(){
        
    }

    string getFileName() {
        return file_name;
    }
    bool isInUse(){
        return inUse;
    }
    void setInUse(bool value){
        inUse = value;
    }
    FsFile* getFsFile(){
        return fs_file;
    }
};


#endif