#include <iostream>
#include "sim_mem.h"
using namespace std;
//char main_memory[MEMORY_SIZE];
int main()
{
    //test 2 - simple main, one process. no read/write to swap. 
    cout<<"=================== test 2 - 15 points ==================="<<endl;
    sim_mem mem_sm2((char*)"test/tester/file1", (char*)"" , (char*)"swap_file" ,5, 10, 5, 5, 5, 5,1);

    mem_sm2.load (1, 4);       //bring 'aaaaa' to frame 0
    mem_sm2.store(1, 8, 'X');  //bring 'bbbXb' to frame 1
    mem_sm2.load (1, 18);      //bring '00000' to frame 2
    mem_sm2.store(1, 21, 'X'); //bring '0X000' to frame 3  
    cout << mem_sm2.load (1, 20 ) << mem_sm2.load (1, 21 ) <<  endl; //print "0X"   


    mem_sm2.print_memory();
	mem_sm2.print_swap();
	mem_sm2.print_page_table();


}
