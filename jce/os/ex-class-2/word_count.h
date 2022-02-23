#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#define ERROR_NULL_STR -1

char* GetInputLineFromUser();

// return ERROR_NULL_STR if failed
int CountWords(char *line);

#endif
