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

#include "FileDescriptor.h"
#include "fsConfig.h"

using namespace std;

class fsDisk {
    FILE *sim_disk_fd;
    bool is_formated;

    // BitVector - "bit" (int) vector, indicate which block in the disk is free
	//              or not.  (i.e. if BitVector[0] == 1 , means that the
	//             first block is occupied.
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
        is_formated = false;
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
    void fsFormat( int blockSize =4 ) {


    }

    // ------------------------------------------------------------------------
    int CreateFile(string fileName) {
 
    }

    // ------------------------------------------------------------------------
    int OpenFile(string fileName) {
  
    }  

    // ------------------------------------------------------------------------
    string CloseFile(int fd) {

    }
    // ------------------------------------------------------------------------
    int WriteToFile(int fd, char *buf, int len ) {


    }
    // ------------------------------------------------------------------------
    int DelFile( string FileName ) {

    }
    // ------------------------------------------------------------------------
    int ReadFromFile(int fd, char *buf, int len ) { 
      
	  
    }

};

#endif