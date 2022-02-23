#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HISTORY_FILE_PATH "history.txt"

#define MAX_LINE_LENGTH 510

int main(void){
    char *history;

    FILE *history_fp = NULL;
    history_fp = fopen(HISTORY_FILE_PATH, "r");

    if(history_fp != NULL){
        size_t text_file_size = 0;

        fseek(history_fp, 0L, SEEK_END);
        text_file_size = ftell(history_fp);
        fseek(history_fp, 0L, SEEK_SET);

        if(text_file_size > 0){
            history = malloc(text_file_size + 1);
            memset(history, 0, text_file_size + 1);
            char current_line[MAX_LINE_LENGTH] = { 0 };
            while((fgets(current_line, MAX_LINE_LENGTH, history_fp)) != NULL)
                strcat(history, current_line); 
        }
        fclose(history_fp);
        history_fp = NULL;
    }
    else{
        history = malloc(1);
        *history = 0;
    }

    char str_input[MAX_LINE_LENGTH] = { 0 };
    while(true){
        printf("Enter String [\'exit\' to exit, \'history\' to print history]: ");

        for(int i = 0; i < MAX_LINE_LENGTH - 1; i++){
            str_input[i] = fgetc(stdin);
            if(str_input[i] == '\n'){
                str_input[i] = 0;
                break;
            }
        }

        if(strcmp(str_input, "exit") == 0)
            break;
        else if(strcmp(str_input, "history") == 0){
            char *line;
            line = strtok(history, "\n");
            int history_entry_num = 0;
            while(line != NULL){
                printf("%d: %s\n", history_entry_num++, line);
                line = strtok(NULL, "\n");
            }
        }
        else{
            unsigned int word_count = 0;
            unsigned int char_count = 0;
            bool in_word = false;
            int i = 0;
            while(str_input[i] != 0){
                if(str_input[i] != ' ' && !in_word){
                    in_word = true;
                    word_count++;
                }

                if(str_input[i] == ' ')
                    in_word = false;
                else
                    char_count++;

                i++;
            }

            printf("%d words\n%d chars\n", word_count, char_count);

            history = realloc(history, strlen(history) + strlen(str_input) + 2);
            if(history[strlen(history) - 1] != '\n')
                strcat(history, "\n");
             
            strcat(history, str_input);
            strcat(history, "\n");
        }
        
    }
    
    history_fp = fopen(HISTORY_FILE_PATH, "w");

    if(history_fp != NULL){
        size_t file_length = strlen(history);
        fwrite(history, file_length, 1, history_fp);
        fclose(history_fp);
        history_fp = NULL;
    }

    free(history);
    return 0;
}