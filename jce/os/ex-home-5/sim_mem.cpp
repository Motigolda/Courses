#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "sim_mem.h"

using namespace std;

typedef enum _error_codes_t{
    ERR_CANT_FIND_FREE_PLACE_IN_SWAP = -6,
    ERR_CANT_FIND_FREE_FRAME = -5, 
    ERR_PAGE_NOT_IN_SWAP = -4, 
    ERR_NULL_PAGE = -3,
    ERR_ILLEGAL_PHYSICAL_ADDRESS = -2,
    ERR_ILLEGAL_LOGIC_ADDRESS = -1
} error_codes_t;

#define ERR_TEMPLATE_FILE_NOT_FOUND "file %s is not found"
#define ERR_MESSAGE_EMPTY_PATH "empty path"
#define MESSAGE_BUFFER_LENGTH (512)
#define GET_FD_OF_PROCESS(process_num, fd_list) fd_list[process_num-1] 
#define IS_PHYSICAL_ADDRESS_LEGAL(address) ( MEMORY_SIZE <= (address) )
#define NOT_IN_MEMORY (-1)
#define NOT_IN_SWAP (-1)
#define IS_PAGE_IN_MEMORY(page) ((page)->frame != NOT_IN_MEMORY)
#define IS_PAGE_IN_SWAP(page) ((page)->swap_index == 1)
#define ERR_CANT_LOAD_PAGE (0)

char main_memory[MEMORY_SIZE];

void print_error_and_exit(const char *error_message);

void print_syscall_error_and_exit(const char *error_message);

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

    this->init_frame_list();

    this->init_swap_index_list();
}
    
sim_mem::~sim_mem(){
    this->close_open_executables();

    close(this->swapfile_fd);

    this->release_dynamicly_allocated_memory();
}

char sim_mem::load(int process_id, int address){
    page_descriptor *page = get_page_by_logical_address(process_id, address);
   
    if (page == NULL)
        return 0;
    
    int page_num = address / page_size;
    int num_of_pages_before_stack_and_heap = (data_size + text_size) / page_size;
    if (page_num > num_of_pages_before_stack_and_heap && page->V == 0){
        printf("Cant load stack and heap before loading other pages of the exectuable!\n");
        return 0;
    }
    int physical_page_address = get_page_physical_address(page, process_id, address / page_size);
    if (physical_page_address < 0)
        return ERR_CANT_LOAD_PAGE;
    
    int offset = get_offest_in_page(address);

    return main_memory[physical_page_address + offset];
}

void sim_mem::store(int process_id, int address, char value){
    page_descriptor *page = get_page_by_logical_address(process_id, address);

    if (page == NULL) 
        return;
    
    if (page->P == 0){
        cout << "Cant store data into text page!" << endl;
        return;
    }
    int physical_address_of_page = this->get_page_physical_address(page, process_id, address / page_size);

    if (physical_address_of_page < 0)
        return;

    int physical_address = 
        physical_address_of_page + this->get_offest_in_page(address);

    main_memory[physical_address] = value;
    page->D = 1;
}
/**************************************************************************************/
void sim_mem::print_memory() {
int i;
printf("\n Physical memory\n");
for(i = 0; i < MEMORY_SIZE; i++) {
printf("[%c]\n", main_memory[i]);
}
}
/************************************************************************************/
void sim_mem::print_swap() {
char* str = (char*)malloc(this->page_size *sizeof(char));
int i;
printf("\n Swap memory\n");
lseek(swapfile_fd, 0, SEEK_SET); // go to the start of the file
while(read(swapfile_fd, str, this->page_size) == this->page_size) {
for(i = 0; i < page_size; i++) {
printf("%d - [%c]\t", i, str[i]);
}
printf("\n");
}
free(str);
}
/***************************************************************************************/
void sim_mem::print_page_table() {
int i;
for (int j = 0; j < num_of_proc; j++) {
printf("\n page table of process: %d \n", j);
printf("Valid\tDirty\tPermission\tFrame\tSwap index\n");
for(i = 0; i < num_of_pages; i++) {
printf("[%d]\t[%d]\t[%d]\t\t[%d]\t[%d]\n",
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
    
    program_fd[fd_index] = open(executable_path, O_RDONLY);

    if (program_fd[fd_index] == -1){
        perror("cant open file");
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
        this->page_table[i] = (page_descriptor*)malloc(sizeof(page_descriptor)*this->num_of_pages);
    
    int first_text_pages_number = text_size / page_size;
    for(i = 0; i < this->num_of_proc; i++){
        int j = 0;
        for (j = 0; j < this->num_of_pages; j++){
            if (j < first_text_pages_number)
                this->page_table[i][j].P = 0;
            else
                this->page_table[i][j].P = 1;
            this->page_table[i][j].D = 0;
            this->page_table[i][j].V = 0;
            this->page_table[i][j].frame = -1;
            this->page_table[i][j].swap_index = -1;
        }
    }
}

void sim_mem::init_swap_file(const char *swap_file_path, int page_size, int num_of_pages, int text_pages){
    this->swapfile_fd = open(swap_file_path, 
        O_RDWR | O_CREAT | O_TRUNC, 
        S_IRUSR | S_IWUSR); 
    if(this->swapfile_fd == -1){
        perror("cant open swap file");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    size_t bytes_wrote = 0;
    for (i = 0; i < page_size * (MEMORY_SIZE / page_size); i++){
        bytes_wrote = write(this->swapfile_fd, "0", 1); 
        if(bytes_wrote == 0){
            perror("cant write to swap file");
            exit(EXIT_FAILURE);
        }
    }
        
}

void sim_mem::init_swap_index_list(){
    size_t size_of_array = num_of_pages*num_of_proc;
    this->swap_index_list = (bool*)malloc(sizeof(bool)*size_of_array);
    int i = 0;
    for (i = 0; i < (int)size_of_array; i++)
        this->swap_index_list[i] = false;
}

void sim_mem::close_open_executables(){
    int i = 0;
    for (i = 0; i < this->num_of_proc; i++)
        close(this->program_fd[i]);
}

void sim_mem::release_dynamicly_allocated_memory(){
    int i = 0;
    for(i = 0; i < this->num_of_proc; i++){
        free(this->page_table[i]);
        this->page_table[i] = NULL;
    }
    free(this->page_table);
    this->page_table = NULL;
    free(this->frame_list);
    free(this->swap_index_list);
}

int sim_mem::get_physical_address(int process_id, int logical_address){
    int page_num = logical_address % this->page_size;
    int offset = get_offest_in_page(logical_address);

    if (page_num < 0 || offset < 0) 
        return ERR_ILLEGAL_LOGIC_ADDRESS;

    if (this->num_of_pages <= page_num)
        return ERR_ILLEGAL_LOGIC_ADDRESS;

    page_descriptor *page = &this->page_table[process_id-1][page_num];
    return get_page_physical_address(page, process_id, logical_address / page_size);
}

int sim_mem::get_page_physical_address(page_descriptor *page, int process_id, int page_index){
    if (IS_PAGE_IN_MEMORY(page))
        return page->frame * this->page_size;
    

    if (IS_PAGE_IN_SWAP(page))
        return this->bring_page_from_swap(page);
    
    int num_of_pages_before_stack_and_heap = (data_size + text_size) / page_size;
    if (page_index < num_of_pages_before_stack_and_heap){
        if (page->D == 0)
            return this->bring_page_from_file(page, process_id, page_index);
        else
            return this->bring_page_from_swap(page);
    }
        

    int free_frame;
    if (is_memory_full())
        free_frame = this->move_oldest_page_from_memory();
    else
        free_frame = get_free_frame_index();

    frame_list[free_frame] = true;
    page->frame = free_frame;
    page->V = 1;
    page->P = 1;
    memset(&main_memory[free_frame*page_size], '0', page_size);
    pages_in_memory.push(free_frame);
    return free_frame*page_size;
}

page_descriptor* sim_mem::get_page_by_logical_address(int process_id, int logical_address){
    int page_num = logical_address / this->page_size;

    if (page_num < 0 || this->num_of_pages <= page_num) {
        printf("Error: out of range of memory.\n");
        return NULL;
    }  
    page_descriptor *page = &this->page_table[process_id-1][page_num];
    return page;
}

int sim_mem::get_offest_in_page(int logical_address){
    int offset = logical_address % this->page_size;
    return offset;
}
// return the physical address of the page
int sim_mem::bring_page_from_file(page_descriptor *page, int process_num, int page_index){
    if (page_index < 0 || this->num_of_pages <= page_index) 
        return ERR_ILLEGAL_LOGIC_ADDRESS;
    int free_frame;
    if (is_memory_full())
        free_frame = this->move_oldest_page_from_memory();
    else
        free_frame = get_free_frame_index();
    int page_offset_in_file = page_index * page_size; 
    int fd = GET_FD_OF_PROCESS(process_num, this->program_fd);
    lseek(fd, page_offset_in_file, SEEK_SET);
    char *buffer = (char*)malloc(sizeof(char)*page_size);
    if(read(fd, buffer, page_size)==0)
        print_syscall_error_and_exit("cant read page from the file");

    int physical_page_address = free_frame*this->page_size;

    memcpy(&main_memory[physical_page_address], buffer, page_size);

    free(buffer);
    this->frame_list[free_frame] = true;
    page->V = 1;
    page->D = 0;
    if (page_index < text_size / page_size)
        page->P = 0;
    else
        page->P = 1;
    page->frame = free_frame;
    pages_in_memory.push(page->frame);
    return physical_page_address;
}

int sim_mem::bring_page_from_swap(page_descriptor *page){
    if (page == NULL)
        return ERR_NULL_PAGE;
    
    if (!IS_PAGE_IN_SWAP(page))
        return ERR_PAGE_NOT_IN_SWAP;

    int free_frame;
    if (is_memory_full())
        free_frame = this->move_oldest_page_from_memory();
    else
        free_frame = this->get_free_frame_index();

    int offset_in_swap = page->swap_index * this->page_size;

    lseek(this->swapfile_fd, offset_in_swap, SEEK_SET);

    char *buffer = (char*)malloc(sizeof(char)*this->page_size);

    if(read(offset_in_swap, buffer, SEEK_SET)==0)
        print_error_and_exit("cant read from swap file");
    
    int physical_page_address = free_frame*this->page_size;

    memcpy(&main_memory[physical_page_address], buffer, this->page_size);

    lseek(this->swapfile_fd, offset_in_swap, SEEK_SET);

    memset(buffer, '0', page_size);

    if(write(this->swapfile_fd, buffer, page_size)==-1)
        print_error_and_exit("cant write to swap file");

    free(buffer);

    this->frame_list[free_frame] = true;
    this->pages_in_memory.push(free_frame);
    page->V = 1;
    page->frame = free_frame;
    page->swap_index = NOT_IN_SWAP;
    return physical_page_address;
}

void sim_mem::init_frame_list(){
    this->frame_list = (bool*)malloc((sizeof(bool)*this->num_of_pages));
    int i = 0;    
    for (i = 0; i < this->num_of_pages; i++)
        this->frame_list[i] = false;
}

int sim_mem::get_free_frame_index(){
    int i = 0;


    for(i = 0; i < this->num_of_pages; i++)
        if (this->frame_list[i] == false)
            return i;

    return ERR_CANT_FIND_FREE_FRAME;
}

int sim_mem::move_oldest_page_from_memory(){
    frame_index free_frame = this->pages_in_memory.front();
    page_descriptor *page = NULL;
    int process_indexer = 0;
    int page_indexer = 0;
    for(process_indexer = 0; process_indexer < this->num_of_proc; process_indexer++){
        for (page_indexer = 0; page_indexer < this->num_of_pages; page_indexer++){
            if (page_table[process_indexer][page_indexer].frame == free_frame)
                page = &page_table[process_indexer][page_indexer];
        }
    }
    if (page->V == 0){
        pages_in_memory.pop();
        return move_oldest_page_from_memory();
    }
    return move_page_from_memory(page, process_indexer, page_indexer);
}

int sim_mem::move_page_from_memory(page_descriptor *page, int process_id, int page_index){
    if (page == NULL)   
        return 0;
    
    page->V = 0;
    pages_in_memory.pop();
    if (page->P == 0 || page->D == 0){
        frame_list[page->frame] = false;
        return page->frame;
    }
    
    int free_index_in_swap = get_free_index_in_swap();
    int free_frame = page->frame;
    this->swap_index_list[free_index_in_swap] = true;
    lseek(swapfile_fd, free_index_in_swap*page_size , SEEK_SET);
    
    if(write(swapfile_fd, &main_memory[free_frame*page_size], page_size)==-1)
        print_syscall_error_and_exit("cant write to swap file");
    
    this->frame_list[free_frame] = false;
    page->swap_index = free_index_in_swap;
    
    return free_frame;
}
int sim_mem::get_free_index_in_swap(){
    int i = 0;
    for (i = 0; i < num_of_pages*num_of_proc; i++)
        if (this->swap_index_list[i] == false)
            return i;

    return ERR_CANT_FIND_FREE_PLACE_IN_SWAP;
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

void print_syscall_error_and_exit(const char *error_message){
    perror(error_message);
    exit(EXIT_FAILURE);
}

bool sim_mem::is_memory_full(){
    int i = 0;
    for (i = 0; i < MEMORY_SIZE / page_size; i++)
        if(frame_list[i] == false)
            return false;
    
    return true;
}