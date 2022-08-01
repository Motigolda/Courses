#include <iostream>
#include "sim_mem.h"
using namespace std;
//char main_memory[MEMORY_SIZE];
int main()
{
   //test 4 - two processes. write to swap -  only dirty pages! 
    cout<<"=================== test 4 - 15 points ==================="<<endl;
    sim_mem mem_sm4((char*)"test/tester/file1", (char*)"test/tester/file2" , (char*)"swap_file" ,5, 5, 5, 5, 4, 5,2);

    mem_sm4.store(2, 7, 'X');  //bring 'BBXBB' to frame 0
    mem_sm4.load (1, 7);       //bring 'bbbbb' to frame 1
    mem_sm4.store(1, 15, 'X'); //bring 'X0000' to frame 2
    mem_sm4.store(2, 15, 'X'); //bring 'X0000' to frame 3
    mem_sm4.store(2, 6, 'X');  //bring 'BXXBB' to frame 0

    //MEMORY IS FULL, frames 0, 2, 3 are dirty

    mem_sm4.load (1, 0);      //bring 'aaaaa' to frame 0. write 'BXXBB' to swap
    mem_sm4.load (2, 11);     //bring '00000' to frame 1. no write to swap
    mem_sm4.load (2, 0);      //bring 'AAAAA' to frame 2. write 'X0000' to swap

    mem_sm4.print_memory();
	mem_sm4.print_swap();
	mem_sm4.print_page_table();


    
}
