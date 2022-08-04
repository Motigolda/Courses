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
#include "fs.h"

using namespace std;



int main() {
    int blockSize; 
	int direct_entries;
    string fileName;
    char str_to_write[DISK_SIZE];
    char str_to_read[DISK_SIZE];
    int size_to_read; 
    int _fd;

    fsDisk *fs = new fsDisk();
    int cmd_;
    cout << "Welcome to file system simulator!" << endl;
    cout << "0 - exit" << endl;
    cout << "1 - list files and show disk content" << endl;
    cout << "2 - format (must be done before any operation" << endl;
    cout << "3 - create a new file" << endl;
    cout << "4 - open an existing file" << endl;
    cout << "5 - close an opened file" << endl;
    cout << "6 - Write text to an opened file" << endl;
    cout << "7 - Read from an opened file" << endl;
    cout << "8 - Delete closed file" << endl;
    cout << "Note that all of the files functionallity available only after formatting the disk (2)" << endl;
    while(1) {
        cout << "|-> ";
        cin >> cmd_;
        switch (cmd_)
        {
            case 0:   // exit
                cout << "Quitting" << endl;
				delete fs;
                cout << "Bye Bye" << endl;
				exit(0);
                break;

            case 1:  // list-file
                fs->listAll(); 
                break;
          
            case 2:    // format
                cout << "-- Formatting --\nEnter Block Size: ";
                cin >> blockSize;
                fs->fsFormat(blockSize);
                cout << "Disk Formatted" << endl;
                break;
          
            case 3:    // create-file
                cout << "-- File creation --\nEnter File Name: ";
                cin >> fileName;
                _fd = fs->CreateFile(fileName);
                cout << "CreateFile: " << fileName << " with File Descriptor #: " << _fd << endl;
                break;
            
            case 4:  // open-file
                cout << "-- File opening --\nEnter File Name: ";
                cin >> fileName;
                _fd = fs->OpenFile(fileName);
                cout << "OpenFile: " << fileName << " with File Descriptor #: " << _fd << endl;
                break;
             
            case 5:  // close-file
                cout << "-- File Closing--\nEnter FD:";
                cin >> _fd;
                fileName = fs->CloseFile(_fd); 
                cout << "CloseFile: " << fileName << " with File Descriptor #: " << _fd << endl;
                break;
           
            case 6:   // write-file
                cout << "-- Writing To File --\nEnter FD:";
                cin >> _fd;
                cout << "Enter Data: ";
                cin >> str_to_write;
                fs->WriteToFile( _fd , str_to_write , strlen(str_to_write) );
                break;
          
            case 7:    // read-file
                cout << "-- Reading From File --\nEnter FD:";
                cin >> _fd;
                cout << "Enter Size To Read: ";
                cin >> size_to_read ;
                fs->ReadFromFile( _fd , str_to_read , size_to_read );
                cout << "ReadFromFile: " << str_to_read << endl;
                break;
           
            case 8:   // delete file 
                cout << "-- Deleting a File --\nEnter File Name: ";
                 cin >> fileName;
                _fd = fs->DelFile(fileName);
                cout << "DeletedFile: " << fileName << " with File Descriptor #: " << _fd << endl;
                break;
            default:
                cout << "Unknown Command" << endl;
                break;
        }
    }

} 