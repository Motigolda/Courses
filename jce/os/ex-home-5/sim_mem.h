#ifndef SIM_MEM_H
#define SIM_MEM_H

#define MEMORY_SIZE (200)
#define EMPTY_MEMORY_CELL_VALUE '0'
#define RETURN_VALUE_IF_CANT_LOAD (0)
#define EMPTY_INDEX (-1)

extern char main_memory[MEMORY_SIZE];

typedef struct page_descriptor
{
    int V; // valid
    int D; // dirty
    int P; // permission
    int frame; //the number of a frame if in case it is page-mapped
    int swap_index; // where the page is located in the swap file.
} page_descriptor;

class sim_mem{
    int swapfile_fd; //swap file fd
    int program_fd[2]; //executable file fd
    int text_size;
    int data_size;
    int bss_size;
    int heap_stack_size;
    int num_of_pages;
    int page_size;
    int num_of_proc;

    page_descriptor **page_table; //pointer to page table

    public:
        sim_mem(const char exe_file_name1[], const char exe_file_name2[], const char swap_file_name[], int
            text_size, int data_size, int bss_size, int heap_stack_size, int num_of_pages, int
            page_size, int num_of_process);
        ~sim_mem();
        char load(int process_id, int address);
        void store(int process_id, int address, char value);
        void print_memory(); // done
        void print_swap (); // done
        void print_page_table(); // done
    private:
        // init functions
        void exit_if_executable_not_exists(const char file_path[]);
        void open_executable(const char executable_path[]);
        void init_virtual_memory();
        void init_page_table(unsigned int num_of_processes);
        void init_swap_file(const char swap_file_path[], int page_size, int num_of_pages, int text_pages);
        // destruct functions
        void close_open_executables();
        void release_dynamicly_allocated_memory();
        void clean_swap_file();
        // page functions 
        int get_physical_address(int logical_address);
        // load functions
        
        // store functions
        bool is_logical_address_text_page(int logical_address);
};

#endif