#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "sim_mem.h"

sim_mem::sim_mem(const char exe_file_name1[], const char exe_file_name2[], const char swap_file_name[], int
    text_size, int data_size, int bss_size, int heap_stack_size, int num_of_pages, int
    page_size, int num_of_process){

}
    
sim_mem::~sim_mem(){

}
char sim_mem::load(int process_id, int address){
    return 0;
}
void sim_mem::store(int process_id, int address, char value){

}
void sim_mem::print_memory() {
    int i;
    printf("\nPhysical memory\n");
    for(i = 0; i < MEMORY_SIZE / 10; i++) {
        printf("[%c]", main_memory[i]);
        if (i % 10) printf("\n");
    }
}
void sim_mem::print_swap() {
    char* str = (char*)malloc(this->page_size *sizeof(char));
    int i;
    printf("\n Swap memory\n");
    lseek(swapfile_fd, 0, SEEK_SET); 
    while(read(swapfile_fd, str, this->page_size) == this->page_size) {
        for(i = 0; i < page_size; i++) {
            printf("%d - [%c]\t", i, str[i]);
        }
        printf("\n");
    }
}
void sim_mem::print_page_table() {
    int i;
    for (int j = 0; j < num_of_proc; j++) {
        printf("\n page table of process: %d \n", j);
        printf("Valid\t Dirty\t Permission \t Frame\t Swap index\n");
        for(i = 0; i < num_of_pages; i++) {
            printf("[%d]\t[%d]\t[%d]\t[%d]\t[%d]\n",
            page_table[j][i].V,
            page_table[j][i].D,
            page_table[j][i].P,
            page_table[j][i].frame ,
            page_table[j][i].swap_index);
        }
    }
}