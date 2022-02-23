#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#define ERROR_NULL_STR -1

// does nothing if line == NULL
// assumes line is dynamic allocated memory
void GetInputLineFromUser(char **line);

// return ERROR_NULL_STR if failed
int CountWords(char *line);

#endif
