#include <iostream>
#include "sim_mem.h"
using namespace std;
//char main_memory[MEMORY_SIZE];
int main()
{

    //test 1 - check only errors. 
    cout<<"=================== test 1 - 15 points ==================="<<endl;
    sim_mem mem_sm1((char*)"test/tester/file1", (char*)"" , (char*)"swap_file" ,5, 10, 5, 5, 5, 5,1);

    mem_sm1.store(1, 30, 'X'); //error - out of range
    mem_sm1.store(1, 4, 'X');  //error - writing to text
    mem_sm1.load (1, 22);      //error - loading heap/stack at the first time

    mem_sm1.print_memory();
	mem_sm1.print_swap();
	mem_sm1.print_page_table();
}
