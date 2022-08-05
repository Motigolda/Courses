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
#include <stdlib.h> 
#include <stdio.h>
#include "fsConfig.h"
#include "FileDescriptor.h"
#include "FsFile.h"

using namespace std;
inline void decToBinary(int, char&);

#define FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(isFormatted) if(!isFormatted) {\
    cout << "FS not formatted!\nSelect option 2 first\n"; \
    return ERROR_OPERATION_FAILED;\
}
#define FAIL_IF_NOT_FORMATTED_AND_RETURN_EMPTY_STRING(isFormatted) if(!isFormatted) {\
    cout << "FS not formatted!\nSelect option 2 first\n"; \
    return "";\
}
#define IS_BLOCK_INDEX_LEGAL(index) (0 <= (index) && (index) < DISK_SIZE / blockSize)
#define EXIT_IF_NULL(ptr) if((ptr) == NULL) {\
    cout << "Null pointer failure" << endl;\
    exit(EXIT_FAILURE);}
#define EXIT_IF_ILLEGAL_BLOCK_INDEX(blockIndex)         if(!IS_BLOCK_INDEX_LEGAL(blockIndex)){\
    cout << "Illegal block index" << endl;\
    exit(EXIT_FAILURE);\
}

class fsDisk {
    FILE *sim_disk_fd;
    bool is_formated;

    // BitVector - "bit" (int) vector, indicate which block in the disk is free
	//              or not.  (i.e. if BitVector[0] == 1 , means that the
	//             first block is occupied.
    int blockSize;
    int BitVectorSize;
    int *BitVector = NULL;
    int maxFileSize;
    vector<FileDescriptor*> MainDir  = {};
    // Structure that links the file name to its FsFile
    map<int, FileDescriptor*> OpenFileDescriptors = {};
    

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
        
        maxFileSize = BLOCK_SIZE_UNDEFINED;

        is_formated = false;
    }
	~fsDisk(){
        cout << "Deleting File System" << endl;
        for (unsigned int file = 0; file < MainDir.size(); file++){
            delete MainDir[file]->getFsFile();
        }
        for (int file = MainDir.size() - 1; file >= 0; file--){
            delete MainDir[file];
        }
        MainDir.clear();
        
        OpenFileDescriptors.clear();

        if (BitVector != NULL)
            free(BitVector);
        fwrite("\0", 1, DISK_SIZE, sim_disk_fd);
        fclose(sim_disk_fd);
    }
    // ------------------------------------------------------------------------
    void listAll() {
        unsigned int i = 0;    
        
        for (i = 0; i < MainDir.size(); i++) {// ITERATE ALL FILE DESCRPTIORS
            cout << "index: " << i << ": FileName: " << MainDir[i]->getFileName()  <<  ", isInUse: ";
            if(MainDir[i]->isInUse())
                cout << "true";
            else
                cout << "false";
            cout << endl;
        }

        char bufy;
        cout << "Disk content: '";
        for (i = 0; i < DISK_SIZE; i++)
        {
            cout << "(";
            fseek(sim_disk_fd, i, SEEK_SET);
            fread(&bufy, 1, 1, sim_disk_fd);
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

        maxFileSize = blockSize*blockSize;
        
        is_formated = true;
    }

    // ------------------------------------------------------------------------
    int CreateFile(string fileName) {
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);
        
        if(GetFilePlaceInMainDir(fileName) != ERROR_FILE_NOT_FOUND){
            cout << "Cannot create " << fileName << ": the file already exists." << endl;
            return ERROR_OPERATION_FAILED; 
        }

        if(fileName.empty()){
            cout << "Cannot create the file because file name is empty!" << endl;
            return ERROR_OPERATION_FAILED;
        }

        FsFile *newFile = new FsFile(this->blockSize);

        FileDescriptor *newFD = new FileDescriptor(fileName, newFile);

        MainDir.push_back(newFD);
        
        return OpenFile(fileName);   
    }

    // ------------------------------------------------------------------------
    int OpenFile(string fileName) {
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);
        int placeInMainDir = GetFilePlaceInMainDir(fileName);
        if (placeInMainDir == ERROR_FILE_NOT_FOUND){
            cout << "Cannot open the file " << fileName << " because its not exists!" << endl;
            return ERROR_OPERATION_FAILED;
        }

        int fd = GetOpenedFileFD(fileName);
        if (fd != ERROR_FD_NOT_EXISTS){
            cout << "Cannot open the file " << fileName << " because its already open!" << endl;
            return ERROR_OPERATION_FAILED;
        }
        
        MainDir[placeInMainDir]->setInUse(true);

        OpenFileDescriptors[placeInMainDir] = MainDir[placeInMainDir];
        
        return placeInMainDir;    
    }  

    // ------------------------------------------------------------------------
    string CloseFile(int fd) {
        FAIL_IF_NOT_FORMATTED_AND_RETURN_EMPTY_STRING(is_formated);

        if (OpenFileDescriptors.count(fd) == 0){
            cout << "The FD " << fd << " does not exists" << endl;
            return "";
        }

        string fileName = OpenFileDescriptors[fd]->getFileName();
        OpenFileDescriptors[fd]->setInUse(false);

        OpenFileDescriptors.erase(fd);

        return fileName;
    }
    // ------------------------------------------------------------------------
    int WriteToFile(int fd, char *buf, int len ) {
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);

        EXIT_IF_NULL(buf);

        if (!IsFileOpen(fd)){
            cout << "File is not opened!" << endl;
            return ERROR_FD_NOT_EXISTS;
        }

        if(len < 1){
            cout << "cant write length < 1" << endl;
            return ERROR_LEN_ZERO;
        }

        if (len > blockSize*blockSize){
            cout << "Length too high, max length is " << blockSize*blockSize << endl;
            return ERROR_LEN_TOO_BIG;
        }

        if (len > GetFreeSpaceLeftOnDisk()){
            cout << "No more space on disk, delete files" << endl;
            return ERROR_DISK_IS_FULL;
        }

        if (len > GetFileFreeSpace(fd)){
            cout << "Not enough space in file" << endl;
            return ERROR_FILE_IS_FULL;
        }

        char *bufferForWriting = (char*)malloc(sizeof(char)*blockSize);

        // try to write to the last block
        int offsetInBuffer = 0;
        int indexOfLastBlockOfFile = GetIndexOfLastBlockOfFile(fd);
        if (indexOfLastBlockOfFile != NOT_DEFINED){
            ReadBlock(indexOfLastBlockOfFile, bufferForWriting);

            int indexOfFreeSpace = strnlen(bufferForWriting, blockSize);

            while(indexOfFreeSpace < blockSize && offsetInBuffer < len){
                bufferForWriting[indexOfFreeSpace] = buf[offsetInBuffer];
                indexOfFreeSpace++;
                offsetInBuffer++;
            }

            WriteBlock(indexOfLastBlockOfFile, bufferForWriting);
        }

        int indexOfBlockForWriting = -1;

        int indexBlock = GetIndexBlockOfFile(fd);
        if (indexBlock == NOT_DEFINED)
            indexBlock = InitFDIndexBlock(fd);
        int newBlockCounter = 0;
        int remainingBytesToWrite = len - offsetInBuffer;
        while(offsetInBuffer < len){
            memset(bufferForWriting, 0, blockSize);

            indexOfBlockForWriting = GetNextFreeBlockIndex();

            memcpy(bufferForWriting, &buf[offsetInBuffer], min(blockSize, remainingBytesToWrite));

            WriteBlock(indexOfBlockForWriting, bufferForWriting);

            AddIndexToIndexBlock(indexBlock, indexOfBlockForWriting);

            offsetInBuffer += 4;
            remainingBytesToWrite = len - offsetInBuffer;
            newBlockCounter++;
        }
        
        free(bufferForWriting);

        FsFile *f = OpenFileDescriptors[fd]->getFsFile();
        f->setBlocksInUse(f->getBlocksInUse() + newBlockCounter);
        f->setFileSize(f->getfile_size() + len);
        return SUCCESS;
    }
    // ------------------------------------------------------------------------
    int DelFile( string FileName ) {
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);  

        int fd = GetFilePlaceInMainDir(FileName);
        if(!isFdExists(fd)){
            cout << "Cant delet file because its not exists!" << endl;
            return ERROR_OPERATION_FAILED;
        }

        if(IsFileOpen(fd)){
            cout << "Cant delete an opened file!" << endl;
            return ERROR_OPERATION_FAILED;
        }
        OpenFile(FileName);
        int indexBlock = GetIndexBlockOfFile(fd);
        CloseFile(fd);
        if (indexBlock != -1){
            int i = 0;
            int currentBlockIndex = GetIndexFromIndexBlock(indexBlock, i);
            while(currentBlockIndex != -1 && i < blockSize){
                CleanBlockAndReleaseForFurtherUse(currentBlockIndex);
                i++;
                currentBlockIndex = GetIndexFromIndexBlock(indexBlock, i);
            }
            CleanBlockAndReleaseForFurtherUse(indexBlock);
        }
        FsFile *f = MainDir[fd]->getFsFile();

        f->resetData();
        delete f;
        delete MainDir[fd];

        MainDir.erase(MainDir.begin() + fd);
        for (unsigned int i = 0; i <= MainDir.size();i++){
            if (OpenFileDescriptors.count(i) > 0){
                OpenFileDescriptors.erase(i);
            }
                
        }
        for (unsigned int i = 0; i < MainDir.size();i++){
            if (MainDir[i]->isInUse()){
                OpenFileDescriptors[i] = MainDir[i];
            }
        }
        return SUCCESS;
    }
    // ------------------------------------------------------------------------
    int ReadFromFile(int fd, char *buf, int len ) { 
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);

        EXIT_IF_NULL(buf);

        if (!IsFileOpen(fd)){
            cout << "File is not opened!" << endl;
            return ERROR_FD_NOT_EXISTS;
        }

        if(len < 1){
            cout << "cant read length < 1" << endl;
            return ERROR_LEN_ZERO;
        }

        if (len > GetFileSize(fd)){
            cout << "Length too high, file size is " << GetFileSize(fd) << endl;
            return ERROR_LEN_TOO_BIG;
        }

        int indexBlock = GetIndexBlockOfFile(fd);
        
        char *readingBuffer = (char*)malloc(sizeof(char)*blockSize*blockSize);
        int i = 0;
        int currentIndexFromIndexBlock = GetIndexFromIndexBlock(indexBlock, i);
        int offsetInBuffer = 0;
        while(currentIndexFromIndexBlock != -1 && i <= len / blockSize){
            ReadBlock(currentIndexFromIndexBlock, &readingBuffer[offsetInBuffer]);
            i++;
            currentIndexFromIndexBlock = GetIndexFromIndexBlock(indexBlock, i);
            offsetInBuffer += 4;
        }
        memcpy(buf, readingBuffer, len);

        free(readingBuffer);
        return SUCCESS;
    }
    

    
    private:
    int GetFilePlaceInMainDir(string fileName){
        for (unsigned int i = 0; i < MainDir.size(); i++)
            if (MainDir[i]->getFileName() == fileName)
                return i;        

        return ERROR_FILE_NOT_FOUND;
    }

    int GetOpenedFileFD(string fileName){
        int fd = GetFilePlaceInMainDir(fileName);
        if (OpenFileDescriptors.count(fd) > 0)
            return fd;
        return ERROR_FD_NOT_EXISTS;
    }

    int GetFreeSpaceLeftOnDisk(){
        int freeSpace = DISK_SIZE;
        for (int i = 0; i < DISK_SIZE / blockSize; i++){
            if (BitVector[i] == 1)
                freeSpace -= blockSize;
        }
        return freeSpace;
    }

    int GetNextFreeBlockIndex(){
        if (GetFreeSpaceLeftOnDisk() == 0)
            return ERROR_DISK_IS_FULL;

        for (int i = 0; i < DISK_SIZE / blockSize; i++){
            if (BitVector[i] == 0){
                BitVector[i] = 1;
                return i;
            }       
        }

        return ERROR_DISK_IS_FULL;
    }

    bool isFdExists(int fd){
        return 0 <= fd && fd < (int)MainDir.size();
    }

    int GetIndexBlockOfFile(int fd){
        if(!IsFileOpen(fd)){
            cout << "Cant get last block of file, file not opened!" << endl;
            return ERROR_FD_NOT_EXISTS;
        }

        FsFile *f = OpenFileDescriptors[fd]->getFsFile();

        return f->getIndexBlock();
    }
    
    int GetIndexOfLastBlockOfFile(int fd){
        if(!IsFileOpen(fd)){
            cout << "Cant get last block of file, file not opened!" << endl;
            return ERROR_FD_NOT_EXISTS;
        }
        
        int indexBlock = GetIndexBlockOfFile(fd);
        if(indexBlock == NOT_DEFINED)
            return ERROR_OPERATION_FAILED;
        
        int i = blockSize - 1;
        int currentIndex = GetIndexFromIndexBlock(indexBlock, i);
        
        while(currentIndex == -1){
            i--;
            currentIndex = GetIndexFromIndexBlock(indexBlock, i);
        }
        
        int lastBlockIndex = currentIndex;

        return lastBlockIndex;
    }
    
    int InitFDIndexBlock(int fd){
        if(!IsFileOpen(fd)){
            cout << "Cant get last block of file, file not opened!" << endl;
            return ERROR_FD_NOT_EXISTS;
        }

        int currentIndexBlock = GetIndexBlockOfFile(fd);
        if (currentIndexBlock != NOT_INITIALIZED)
            return currentIndexBlock;

        if(GetFreeSpaceLeftOnDisk() < 2*blockSize){
            cout << "Not enough space for a new file, delete files to continue" << endl;
            return ERROR_NOT_ENOUGH_FREE_SPACE;
        }

        FsFile *f = OpenFileDescriptors[fd]->getFsFile();

        int freeBlock = GetNextFreeBlockIndex();

        f->setIndexBlock(freeBlock);
        BitVector[freeBlock] = 1;
        if (f->getIndexBlock() == freeBlock)
            return freeBlock;

        

        return ERROR_OPERATION_FAILED;
    }
    // block functions
    int WriteBlock(int blockIndex, char *buffer){
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);

        EXIT_IF_ILLEGAL_BLOCK_INDEX(blockIndex);

        EXIT_IF_NULL(buffer);

        fseek(sim_disk_fd, blockIndex*blockSize, SEEK_SET);

        size_t bytesWritten = fwrite(buffer, 1, blockSize, sim_disk_fd);
        
        if(bytesWritten > 0)
            BitVector[blockIndex] = 1;

        return bytesWritten;
    }

    int ReadBlock(int blockIndex, char *outputBuffer){
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);

        EXIT_IF_ILLEGAL_BLOCK_INDEX(blockIndex);

        EXIT_IF_NULL(outputBuffer);

        fseek(sim_disk_fd, blockIndex*blockSize, SEEK_SET);

        size_t bytesRead = fread(outputBuffer, 1, blockSize, sim_disk_fd);
        
        if(bytesRead == 0)
            return ERROR_OPERATION_FAILED;

        return (int)bytesRead;
    }

    int AddIndexToIndexBlock(int blockIndex, int indexToAdd){
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);

        EXIT_IF_ILLEGAL_BLOCK_INDEX(blockIndex);

        char *buffer = (char*)malloc(sizeof(char)*blockSize);

        ReadBlock(blockIndex, buffer);

        int i = 0;
        while(i < blockSize && buffer[i] != 0)
            ++i;

        if (i == blockSize){
            free(buffer);
            return ERROR_FILE_IS_FULL;
        }


        int freePlaceForIndex = i;

        char toAsciiVal = (char)((unsigned char)indexToAdd + '0');

        buffer[freePlaceForIndex] = toAsciiVal;

        WriteBlock(blockIndex, buffer);

        free(buffer);
        
        return SUCCESS;       
    }

    int GetIndexFromIndexBlock(int blockIndex, int indexPositionInBlock){
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);

        EXIT_IF_ILLEGAL_BLOCK_INDEX(blockIndex);

        if (indexPositionInBlock < 0 || blockSize <= indexPositionInBlock)
            return ERROR_OPERATION_FAILED;

        char *buffer = (char*)malloc(sizeof(char)*blockSize);

        ReadBlock(blockIndex, buffer);

        char indexFromBuffer = buffer[indexPositionInBlock];

        if (indexFromBuffer == 0){
            free(buffer);
            return ERROR_OPERATION_FAILED;
        }

        
        char fromAsciiToVal = (char)((unsigned char)indexFromBuffer - '0');

        free(buffer);

        return fromAsciiToVal;
    }

    int CleanBlockAndReleaseForFurtherUse(int blockIndex){
        EXIT_IF_ILLEGAL_BLOCK_INDEX(blockIndex);

        char *buffer = (char*)malloc(sizeof(char)*blockSize);

        memset(buffer, 0, blockSize);

        WriteBlock(blockIndex, buffer);

        free(buffer);

        BitVector[blockIndex] = 0;

        return SUCCESS;
    }
    // file functions
    bool IsFileOpen(int fd){
        return OpenFileDescriptors.count(fd) > 0;
    }

    int GetFileSize(int fd){
        if (!IsFileOpen(fd))
            return ERROR_OPERATION_FAILED;
        return OpenFileDescriptors[fd]->getFsFile()->getFileSize();
    }
    
    int GetFileFreeSpace(int fd){
        FAIL_IF_NOT_FORMATTED_AND_RETURN_ERROR(is_formated);

        if(!IsFileOpen(fd))
            return ERROR_FILE_NOT_FOUND;
      
        int indexBlockOfFile = GetIndexBlockOfFile(fd);
        
        if (indexBlockOfFile == -1)
            return blockSize * blockSize;


        int currentInitalIndexInIndexBlock = 0;
        
        int currentBlockIndex = 0;

        int nextIndex = 0;
        nextIndex = GetIndexFromIndexBlock(indexBlockOfFile, currentInitalIndexInIndexBlock);
        
        while(nextIndex != -1){
            currentInitalIndexInIndexBlock++;
            currentBlockIndex = nextIndex;
            nextIndex = GetIndexFromIndexBlock(indexBlockOfFile, currentInitalIndexInIndexBlock);
        }
        
        int lastBlockIndex = currentBlockIndex;

        char *buffer = (char*)malloc(sizeof(char)*blockSize);

        ReadBlock(lastBlockIndex, buffer);

        int freeBytesInLastBlock = blockSize - strnlen(buffer, blockSize);

        free(buffer);

        int freeBytesInFile = 
            (blockSize * blockSize) - (min(currentInitalIndexInIndexBlock, blockSize)*blockSize) + freeBytesInLastBlock;

        return freeBytesInFile;
    }
};

#endif