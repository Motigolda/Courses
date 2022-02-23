#include <stdio.h>

#include "word_count.h"

char* GetInputLineFromUser(){
    
}

int CountWords(char *line){
    if (line == NULL)   
        return ERROR_NULL_STR;
    
    int words_count = 0;
    int i = 0;
    while(line[i] != 0){
        if (line[i] == ' ')
            words_count++;

        i++;
    }
    return words_count;
}
