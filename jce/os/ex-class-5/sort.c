#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#pragma region Usefull Defines

// Empty macro that helps to define output vars
#define OUT 

#pragma endregion // Usefull Defines

#pragma region Sizes And Numbers

#define ARRAY_SIZE          (20)
#define MAX_RANDOM_NUMBER   (100)
#define MIN_RANDOM_NUMBER   (0)
#define NUMBER_MAX_TEXT_LEN (21)

#pragma endregion // Size And Numbers

#pragma region Strings And Templates

#define PARENT_MIN_AND_MAX_PRINT_TEMPLATE "I got %s %s\n"
#define SON_MIN_AND_MAX_PRINT_TEMPLATE "%d %d"

#pragma endregion // Strings And Templates

#pragma region Multi Processing Functions

void ArrayRandomizingFlow(int* array, size_t array_length);

void SonArraySortingFlow(int* pipe_fd, int* array, size_t array_length);

void ParentMinMaxPrintFlow(int* pipe_fd);

void ExitWithPerror(char* error_text);

#pragma endregion // Multi Processing Functions

#pragma region Array Functions

void SetArrayRandomNumbers(int* array, size_t array_length);

void SortArray(int* array, size_t array_length);

int CompareForQSort(const void* a, const void* b);

void GetMinAndMaxInSortedArray(int* sorted_array, size_t array_length, 
    OUT int* min_from_array, OUT int* max_from_array);

#pragma endregion

#pragma region Print Functions

void PrintMinAndMax(int min, int max);

void PrintErrorTextAndExit(char* error_text);

#pragma endregion // Print Functions

int main(void){
    srand(time(NULL));

    int array_to_sort[ARRAY_SIZE] = { 0 };

    ArrayRandomizingFlow(array_to_sort, ARRAY_SIZE);

    int pipe_fd[2] = { 0 };
    
    bool pipe_creation_success = pipe(pipe_fd) != -1;

    if (!pipe_creation_success)
        ExitWithPerror("Can\'t create pipe");

    pid_t my_pid = fork();

    if(my_pid == 0)
        SonArraySortingFlow(pipe_fd, array_to_sort, ARRAY_SIZE);
    else if (0 < my_pid)
        ParentMinMaxPrintFlow(pipe_fd);
    else 
        ExitWithPerror("Can\'t create son");

    return 0;
}

void ArrayRandomizingFlow(int* array, size_t array_length){
    if (array == NULL)
        PrintErrorTextAndExit("Null pointer to array");

    if (array_length == 0)
        PrintErrorTextAndExit("Array length is 0");

    SetArrayRandomNumbers(array, array_length);   
}

void SonArraySortingFlow(int* pipe_fd, int* array, size_t array_length){
    SortArray(array, array_length);

    int array_min;
    int array_max;

    GetMinAndMaxInSortedArray(array, array_length, &array_min, &array_max);

    if(close(pipe_fd[0]) == -1)
        ExitWithPerror("Can\'t close pipe_fd[0]");

    if(dup2(pipe_fd[1], fileno(stdout)) == -1)
        ExitWithPerror("Can\'t dup2(stdout)");

    PrintMinAndMax(array_min, array_max);

    close(pipe_fd[1]);
}

void ParentMinMaxPrintFlow(int* pipe_fd){
    if (pipe_fd == NULL)
        PrintErrorTextAndExit("Null pointer to pipe_fd");

    if(close(pipe_fd[1]) == -1)
        ExitWithPerror("Can\'t close pipe_fd[1]");

    if(dup2(pipe_fd[0], fileno(stdin)) == -1)
        ExitWithPerror("Can\'t close dup2(stdin)");
  
    char num1_text[NUMBER_MAX_TEXT_LEN] = { 0 };
    scanf("%s", num1_text);
    char num2_text[NUMBER_MAX_TEXT_LEN] = { 0 };
    scanf("%s", num2_text);

    close(pipe_fd[0]);

    printf(PARENT_MIN_AND_MAX_PRINT_TEMPLATE, num1_text, num2_text);
}

void ExitWithPerror(char* error_text){
    perror(error_text);
    exit(EXIT_FAILURE);
}

void SetArrayRandomNumbers(int* array, size_t array_length){
    if (array == NULL)
        return;

    if (array_length == 0)
        return;

    for (int i = 0; i < array_length; i++)
        array[i] = MIN_RANDOM_NUMBER + 
            (rand() % (MAX_RANDOM_NUMBER - MIN_RANDOM_NUMBER));
}

void SortArray(int* array, size_t array_length){
    if (array == NULL)
        PrintErrorTextAndExit("Null pointer to array");

    if (array_length == 0)
        PrintErrorTextAndExit("Array length is 0");
    
    qsort(array, array_length, sizeof(int), CompareForQSort);
}

int CompareForQSort(const void* a, const void* b){
    int a1 = *((int*)a);
    int b1 = *((int*)b);

    if (a1 > b1) return 1;
    if (a1 < b1) return -1;

    return 0;
}

void GetMinAndMaxInSortedArray(int* sorted_array, size_t array_length, 
    OUT int* min_from_array, OUT int* max_from_array){
    if (sorted_array == NULL)
        PrintErrorTextAndExit("Null pointer to array");

    if (array_length == 0)
        PrintErrorTextAndExit("Array length is 0");

    if (min_from_array == NULL)
        PrintErrorTextAndExit("Null pointer to min from array");

    if (max_from_array == NULL)
        PrintErrorTextAndExit("Null pointer to max from array");

    *min_from_array = sorted_array[0];
    *max_from_array = sorted_array[array_length - 1];
}

void PrintMinAndMax(int min, int max){
    printf(SON_MIN_AND_MAX_PRINT_TEMPLATE, min, max);
}

void PrintErrorTextAndExit(char* error_text){
    printf("%s\n", error_text);
    exit(EXIT_FAILURE);
}
