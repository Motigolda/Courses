#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HISTORY_FILE_PATH "history.txt"

#define WAIT_FOR_USER_INPUT_STR "Enter String, or \"exit\" to end program:\n"
#define CMD_EXIT_STR "exit"
#define CMD_PRINT_HISTORY_STR "history"

#define MAX_LINE_LENGTH 510

#define OUT

typedef struct _history_t{
    // Assumes that history_string is always dynamically allocated
    char *history_string;
} history_t;

typedef struct _line_stats_t{
    unsigned int word_count;
    unsigned int char_count;
    char first_word_buffer[MAX_LINE_LENGTH];
} line_stats_t;

typedef enum _user_command_t{
    CMD_UNKNOWN = -1,
    CMD_PRINT_STATS = 0,
    CMD_PRINT_HISTORY,
    CMD_EXIT,
    CMD_EMPTY_LINE
} user_command_t;

long GetFileSize(char* file_path){
    if (file_path == NULL)
        return -1;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL)
        return -1;
    
    fseek(fp, 0L, SEEK_END);
    long text_file_size = ftell(fp);
    
    fclose(fp);

    return text_file_size;
}

void ReadTextFile(char* file_path, OUT char* file_text, long file_size){
    if (file_path == NULL) 
        return;

    if (file_text == NULL) 
        return;

    if (file_size < 0)
        file_size = GetFileSize(file_path);

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL)
        return;

    memset(file_text, 0, file_size);

    char current_line[MAX_LINE_LENGTH] = { 0 };
    
    while((fgets(current_line, MAX_LINE_LENGTH, fp)) != NULL)
        strcat(file_text, current_line); 
    
    fclose(fp);
}       

void SaveTextFile(char* file_path, char* file_text){
    if (file_path == NULL)
        return;

    if (file_text == NULL)
        return;

    FILE *fp = fopen(file_path ,"w");
    if (fp == NULL)
        return;

    fwrite(file_text, strlen(file_text), 1, fp);

    fclose(fp);
}

history_t* LoadHistoryFromFile(char* history_file_path){
    if (history_file_path == NULL)
        return NULL;
    
    long file_size = GetFileSize(history_file_path);
    
    static history_t history = { 0 };

    if (file_size > 0){
        history.history_string = malloc(file_size + 1);

        memset(history.history_string, 0, file_size + 1);

        ReadTextFile(history_file_path, history.history_string, file_size);
    }
    else{
        history.history_string = malloc(1);
        *history.history_string = 0;
    }

    return &history;
}

void SaveHistoryToFile(history_t *history, char* history_file_path){
    if (history == NULL)  
        return;

    if (history_file_path == NULL)
        return;

    SaveTextFile(history_file_path, history->history_string);
}

void AppendEntryToHistory(history_t *history, char *entry){
    if (history == NULL || history->history_string == NULL)
        return;

    if (entry == NULL)
        return;

    size_t current_history_string_len = strlen(history->history_string);
    size_t new_entry_len = strlen(entry); 
    
    history->history_string = realloc(history->history_string, current_history_string_len + new_entry_len + 1);
    
    if (current_history_string_len > 0 &&
        history->history_string[current_history_string_len - 1] != '\n')
        strcat(history->history_string, "\n");

    strcat(history->history_string, entry);
}

void PrintHistory(history_t *history){
    if (history == NULL)
        return;

    char *history_copy = malloc(strlen(history->history_string) + 1);
    strcpy(history_copy, history->history_string);

    char *line_in_history;
    line_in_history = strtok(history_copy, "\n");
    unsigned int history_entry_num = 0;

    while(line_in_history != NULL){
        printf("%u: %s\n", history_entry_num++, line_in_history);
        line_in_history = strtok(NULL, "\n");
    }

    free(history_copy);
    
}

line_stats_t* GetLineStats(char *line){
    if (line == NULL)
        return NULL;

    static line_stats_t stats = { 0 };

    bool in_word = false;
    int i = 0;
    int first_line_buffer_index = 0;

    while(line[i] != 0 && line[i] != '\n'){
        if(line[i] != ' ' && !in_word){
            in_word = true;
            stats.word_count++;
        }

        if(line[i] == ' ')
            in_word = false;
        else
            stats.char_count++;

        if(stats.word_count == 1 && line[i] != ' '){
            stats.first_word_buffer[first_line_buffer_index] = line[i];
            first_line_buffer_index++;
        }

        i++;
    }
    
    return &stats;
}

void PrintLineStats(line_stats_t* stats){
    if (stats == NULL)
        return;

    printf("%u words\n", stats->word_count);
    printf("%u chars\n", stats->char_count);
}

user_command_t GetSelectedCommand(line_stats_t *stats){
    if(stats == NULL)
        return CMD_UNKNOWN;

    if (stats->word_count > 1)
        return CMD_PRINT_STATS;

    if (strcmp(stats->first_word_buffer, CMD_PRINT_HISTORY_STR) == 0)
        return CMD_PRINT_HISTORY;
    
    if (strcmp(stats->first_word_buffer, CMD_EXIT_STR) == 0)
        return CMD_EXIT;
    
    if (stats->word_count == 0 && stats->char_count == 0)
        return CMD_EMPTY_LINE;

    return CMD_PRINT_STATS;
    
}

void GetLineFromUser(OUT char *line_from_user){
    if (line_from_user == NULL)
        return;

    memset(line_from_user, 0, MAX_LINE_LENGTH);

    printf(WAIT_FOR_USER_INPUT_STR);


    fgets(line_from_user, MAX_LINE_LENGTH, stdin);

    line_from_user[MAX_LINE_LENGTH - 1] = 0;
}

void FreeHistoryInstanceString(history_t* history){
    if (history == NULL)
        return;
    
    if (history->history_string == NULL)
        return;

    free(history->history_string);
    history->history_string = NULL;
}

int main(void){
    history_t* history = LoadHistoryFromFile(HISTORY_FILE_PATH);
    
    if (history == NULL){
        printf("Cant read history from path: %s\nhistory object is null.\n", HISTORY_FILE_PATH);
        exit(1);
    }

    char input_line[MAX_LINE_LENGTH] = { 0 }; 

    line_stats_t *stats = NULL;

    user_command_t current_selected_command = -1;

    while (current_selected_command != CMD_EXIT){
        GetLineFromUser(input_line);

        stats = GetLineStats(input_line);

        current_selected_command = GetSelectedCommand(stats);

        switch (current_selected_command)
        {
            case CMD_EMPTY_LINE:
                break;
            case CMD_PRINT_STATS:
                PrintLineStats(stats);
                AppendEntryToHistory(history, input_line);
                break;
            case CMD_PRINT_HISTORY:
                PrintHistory(history);
                break;
            case CMD_EXIT:
                break;
            default:
                printf("Unknown Failure\n");
                break;
        }
        stats->char_count = 0;
        stats->word_count = 0;
        memset(stats->first_word_buffer, 0, MAX_LINE_LENGTH);        
    }

    SaveHistoryToFile(history, HISTORY_FILE_PATH);

    FreeHistoryInstanceString(history);
    
    return 0;
}