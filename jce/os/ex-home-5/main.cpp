#include <iostream>
#include "sim_mem.h"
using namespace std;
//char main_memory[MEMORY_SIZE];
int main()
{
    //test 3 - one process. text pages are loaded and are not written to swap
    cout<<"=================== test 3 - 15 points ==================="<<endl;
    sim_mem mem_sm3((char*)"test/tester/file1", (char*)"" , (char*)"swap_file" ,20, 10, 5, 5, 8, 5,1);
	

    mem_sm3.load (1, 17);     //bring 'ddddd' to frame 0
    mem_sm3.load (1, 6);      //bring 'bbbbb' to frame 1
    mem_sm3.load (1, 2);      //bring 'aaaaa' to frame 2
    mem_sm3.store(1, 20, 'X');//bring 'Xeeee' to frame 3
    mem_sm3.store(1, 21, 'Y');//bring 'XYeee' to frame 3

    //MEMORY IS FULL

    mem_sm3.store(1, 37, 'Z');//bring '00Z00' to frame 0. no write to swap
    mem_sm3.load (1, 11);     //bring 'ccccc' to frame 1. no write to swap


    mem_sm3.print_memory();
	mem_sm3.print_swap();
	mem_sm3.print_page_table();


    
}
