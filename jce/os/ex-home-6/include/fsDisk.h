#ifndef FS_DISK_H
#define FS_DISK_H

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
#include <algorithm>

#include "fsConfig.h"
#include "FileDescriptor.h"
#include "FsFile.h"

using namespace std;

#define FAIL_IF_NOT_FORMMATED_AND_RETURN_ERROR(isFormatted) if(!isFormatted) {\
    cout << "FS not formatted!\nSelect option 2 first\n"; \
    return ERROR_OPERATION_FAILED;\
}
#define FAIL_IF_NOT_FORMMATED_AND_RETURN_EMPTY_STRING(isFormatted) if(!isFormatted) {\
    cout << "FS not formatted!\nSelect option 2 first\n"; \
    return "";\
}
class fsDisk {
    FILE *sim_disk_fd;
    bool is_formated;

    // BitVector - "bit" (int) vector, indicate which block in the disk is free
	//              or not.  (i.e. if BitVector[0] == 1 , means that the
	//             first block is occupied.
    int blockSize;
    int BitVectorSize;
    int *BitVector;

    vector<FileDescriptor> MainDir;
    // Structure that links the file name to its FsFile

    vector<FileDescriptor> OpenFileDescriptors;

    //  when you open a file,
    // the operating system creates an entry to represent that file
    // This entry number is the file descriptor.

    // ------------------------------------------------------------------------
    public:
    fsDisk() {
        sim_disk_fd = fopen(DISK_SIM_FILE , "w+");
        assert(sim_disk_fd);

        for (int i=0; i < DISK_SIZE ; i++) {
            int ret_val = fseek ( sim_disk_fd , i , SEEK_SET );
            ret_val = fwrite( "\0" ,  1 , 1, sim_disk_fd);
            assert(ret_val == 1);
        }

        fflush(sim_disk_fd);

        blockSize = BLOCK_SIZE_UNDEFINED;

        is_formated = false;
    }
	~fsDisk(){
        cout << "Deleting File System" << endl;
        for (int file = 0; file < MainDir.size(); file++){
            delete MainDir[file].getFsFile();
        }
        
        MainDir.clear();

        free(BitVector);

        fclose(sim_disk_fd);
    }
    // ------------------------------------------------------------------------
    void listAll() {
        int i = 0;    
        
        for (i = 0; i < MainDir.size(); i++) {// ITERATE ALL FILE DESCRPTIORS
            cout << "index: " << i << ": FileName: " << MainDir[i].getFileName()  <<  " , isInUse: " << MainDir[i].isInUse() << endl;
            i++;
        }

        char bufy;
        cout << "Disk content: '";
        for (i = 0; i < DISK_SIZE; i++)
        {
            cout << "(";
            int ret_val = fseek(sim_disk_fd, i, SEEK_SET);
            ret_val = fread(&bufy, 1, 1, sim_disk_fd);
            cout << bufy;
            cout << ")";
        }
        cout << "'" << endl;
    }


 
    // ------------------------------------------------------------------------
    void fsFormat( int blockSize = 4 ) {
        if (is_formated){
            cout << "Disk already formatted!" << endl;
            return;
        }

        if (blockSize < 1 || DISK_SIZE < blockSize){
            cout << "Block size must 0 < be blockSize < " << DISK_SIZE << endl;
            return;
        }

        BitVectorSize = ((DISK_SIZE) / blockSize) + 1;

        BitVector = (int*)malloc(BitVectorSize*sizeof(int));

        memset(BitVector, 0, BitVectorSize*sizeof(int));

        this->blockSize = blockSize;

        is_formated = true;
    }

    // ------------------------------------------------------------------------
    int CreateFile(string fileName) {
        FAIL_IF_NOT_FORMMATED_AND_RETURN_ERROR(is_formated);
        
        if(isFileExists(fileName)){
            cout << "Cannot create " << fileName << ": the file already exists." << endl;
            return ERROR_OPERATION_FAILED; 
        }

        if(fileName.empty()){
            cout << "Canot create the file because file name is empty!" << endl;
            return ERROR_OPERATION_FAILED;
        }

        FsFile *newFile = new FsFile(this->blockSize);

        FileDescriptor newFD(fileName, newFile);

        MainDir.push_back(newFD);
        
        return SUCCESS;   
    }

    // ------------------------------------------------------------------------
    int OpenFile(string fileName) {
        FAIL_IF_NOT_FORMMATED_AND_RETURN_ERROR(is_formated);

    }  

    // ------------------------------------------------------------------------
    string CloseFile(int fd) {
        FAIL_IF_NOT_FORMMATED_AND_RETURN_EMPTY_STRING(is_formated);
    }
    // ------------------------------------------------------------------------
    int WriteToFile(int fd, char *buf, int len ) {
        FAIL_IF_NOT_FORMMATED_AND_RETURN_ERROR(is_formated);

    }
    // ------------------------------------------------------------------------
    int DelFile( string FileName ) {
        FAIL_IF_NOT_FORMMATED_AND_RETURN_ERROR(is_formated);
    }
    // ------------------------------------------------------------------------
    int ReadFromFile(int fd, char *buf, int len ) { 
        FAIL_IF_NOT_FORMMATED_AND_RETURN_ERROR(is_formated);
	  
    }
    private:
    bool isFileExists(string fileName){
        return false;
    }
};

#endif