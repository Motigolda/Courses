#ifndef WORD_COUNT_H
#define WORD_COUNT_H
// does nothing if line == NULL
// assumes line is dynamic allocated memory
void GetInputLineFromUser(char **line);

// return -1 if failed
int CountWords(char *line);

#endif
