#include <stdio.h>
#include <stdlib.h>

#include "word_count.h"

static void ExitIfNull(void* p, char* msg);

int main(void){

	char *line =  NULL;	
	line = GetInputLineFromUser();

	ExitIfNull(line, "Can\'t get input from user.");

	int word_count = CountWords(line);
	
	if (0 <= word_count)
		printf("The number of words in the given string is: %d.\n", word_count);
	else
		printf("Error occurred.\n");
	
	free(line);

	return 0;
}

static void ExitIfNull(void* p, char* msg){
	if (p != NULL)
		return;

	if (msg != NULL)
		printf("Null Pointer Error: %s\n", msg);

	exit(1);
}