#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "sim_mem.h"

using namespace std;

#define ERR_TEMPLATE_FILE_NOT_FOUND "file %s is not found"
#define ERR_MESSAGE_EMPTY_PATH "empty path"
#define MESSAGE_BUFFER_LENGTH (512)
#define GET_FD_OF_PROCESS(process_num, fd_list) fd_list[process_num-1] 

void print_error_and_exit(const char *error_message);

bool is_file_exists(const char file_path[]);

sim_mem::sim_mem(const char exe_file_name1[], 
    const char exe_file_name2[], 
    const char swap_file_name[], 
    int text_size, 
    int data_size, 
    int bss_size, 
    int heap_stack_size, 
    int num_of_pages, 
    int page_size, 
    int num_of_process){

    this->text_size = text_size;
    this->data_size = data_size;
    this->bss_size = bss_size;
    this->heap_stack_size = heap_stack_size;
    this->num_of_pages = num_of_pages;
    this->page_size = page_size;
    this->num_of_proc = num_of_process;
    this->swapfile_fd = -1;
    this->program_fd[0] = -1;
    this->program_fd[1] = -1;

    this->exit_if_executable_not_exists(exe_file_name1);
    if (num_of_process == 2)
        this->exit_if_executable_not_exists(exe_file_name2);

    this->open_executable(exe_file_name1);
    if (num_of_process == 2)
        this->open_executable(exe_file_name2);
        
    this->init_swap_file(swap_file_name, 
        page_size, 
        num_of_pages, 
        (text_size / page_size)+1);

    this->init_virtual_memory();

    this->init_page_table(num_of_process);
}
    
sim_mem::~sim_mem(){
    int i = 0;
    for (i = 0; i < this->num_of_proc; i++)
        close(this->program_fd[i]);

    this->clean_swap_file();
    close(this->swapfile_fd);

}

char sim_mem::load(int process_id, int address){
    return 0;
}

void sim_mem::store(int process_id, int address, char value){

}

void sim_mem::print_memory() {
    int i;
    printf("\nPhysical memory\n");
    for(i = 0; i < MEMORY_SIZE; i++) {
        printf("[%c]", main_memory[i]);
        if ((i+1) % 10 == 0) 
            printf("\n");
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

void sim_mem::exit_if_executable_not_exists(const char file_path[]){
    if(is_file_exists(file_path))
        return;

    char message_buffer[MESSAGE_BUFFER_LENGTH] = { 0 };

    if (file_path != nullptr && strcmp(file_path, "") != 0)
        sprintf(message_buffer, ERR_TEMPLATE_FILE_NOT_FOUND, file_path);
    else 
        strcpy(message_buffer, ERR_MESSAGE_EMPTY_PATH);

    print_error_and_exit(message_buffer);
}
// assumes path checked
void sim_mem::open_executable(const char executable_path[]){
    if (executable_path == nullptr)
        return;

    unsigned int fd_index = 0;
    
    while(this->program_fd[fd_index] != -1)
        fd_index++;
    
    program_fd[fd_index] = open(executable_path, O_RDONLY | O_TRUNC);

    if (program_fd[fd_index] == -1){
        perror("cant open swap file");
        exit(EXIT_FAILURE);
    }
}
void sim_mem::init_virtual_memory(){
    int i = 0;
    for (i = 0; i < MEMORY_SIZE; i++)
        main_memory[i] = EMPTY_MEMORY_CELL_VALUE;
}
void sim_mem::init_page_table(unsigned int num_of_processes){
    if (num_of_processes < 1 || num_of_processes > 3)
        exit(EXIT_FAILURE);

    this->page_table = (page_descriptor**)malloc(sizeof(page_descriptor*) * this->num_of_proc);
    int i = 0;
    for(i = 0; i < this->num_of_proc; i++)
        this->page_table = malloc(sizeof(page_descriptor)*this->num_of_pages);
    
}

void sim_mem::init_swap_file(const char *swap_file_path, int page_size, int num_of_pages, int text_pages){
    this->swapfile_fd = open(swap_file_path, 1); // find the right flags

    int i = 0;
    for (i = 0; i < page_size * (num_of_pages - text_pages); i++)
        write(this->swapfile_fd, "0", 1); 
}

bool is_file_exists(const char file_path[]){
    if (file_path == nullptr)
        return false;

    FILE *file = fopen(file_path, "r");
    
    if(file != 0){
        fclose(file);
        return true;
    }

    return false;
}

void print_error_and_exit(const char *error_message){
    cout << "Error: " << error_message << endl;
    exit(EXIT_FAILURE);
}

