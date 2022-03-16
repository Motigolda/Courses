#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma region Usefull Defines

// Empty macro that helps to define output vars
#define OUT 

#pragma endregion // Usefull Defines

#pragma region Sizes And Numbers

#define ARRAY_SIZE          (20)
#define MAX_RANDOM_NUMBER   (100)
#define MIN_RANDOM_NUMBER   (0)

#pragma endregion // Size And Numbers

#pragma region Strings And Templates

#define MIN_AND_MAX_PRINT_TEMPLATE "I got %d %d\n"

#pragma endregion // Strings And Templates

#pragma region Multi Processing Functions

void PreMultiProcessingFlow(int* array, size_t array_length);

bool SonFlow(int* array, size_t array_length);

bool ParentFlow();

void ExitWithPerror(char* error_text);

#pragma endregion // Multi Processing Functions

#pragma region Array Functions

void SetArrayRandomNumbers(int* array, size_t array_length);

void SortArray(int* array, size_t array_length);

void GetMinAndMaxInArray(int* sorted_array, size_t array_length, OUT int* min, OUT int* max);

#pragma endregion

#pragma region Print Functions

void PrintMinAndMax(int min, int max);

#pragma endregion // Print Functions

int main(void){
    int array_to_sort[ARRAY_SIZE] = { 0 };

    PreMultiProcessingFlow(array_to_sort, ARRAY_SIZE);

    pid_t current_pid = fork();

    if(current_pid == 0)
        SonFlow(array_to_sort, ARRAY_SIZE);
    else if (0 < current_pid)
        ParentFlow();
    else 
        ExitWithPerror("Can't create new son");

    return 0;
}

void PreMultiProcessingFlow(int* array, size_t array_length){
    if (array == NULL)
        return;

    if (array_length == 0)
        return;

    SetArrayRandomNumbers(array, array_length);   
}