#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "word_count.h"

char* GetInputLineFromUser(){
    printf("Enter a line of text:\n");

    int line_length = 1;
    char* line = malloc(line_length);
    
    if(line == NULL)
        return NULL;
    
    char current_input_char;
    char *old_line = NULL;
    int i = 0;
    
    while((current_input_char = fgetc(stdin)) != '\n' && current_input_char != '\0'){
        old_line = line;        
        line = realloc(old_line, line_length + 1);
        
        if (line == NULL)
            return NULL;

        strncpy(line, old_line, line_length);
        ++line_length;

        line[i] = current_input_char;
        i++;
    }

    line = realloc(line, line_length + 1);
    if (line == NULL)
        return NULL;
    
    line[i] = '\0';

    return line;
}

int CountWords(char *line){
    if (line == NULL)   
        return ERROR_NULL_STR;
    
    int words_count = 0;
    int i = 0;
    bool in_word = false;
    while(line[i] != 0){
        if(line[i] != ' ' && !in_word){
            in_word = true;
            words_count++;
        }

        if(line[i] == ' ')
            in_word = false;

        i++;
    }

    return words_count;
}
