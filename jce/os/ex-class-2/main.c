#include <stdio.h>
#include <stdlib.h>

#include "word_count.h"

int main(void){

	char *line =  NULL;	
	line = GetInputLineFromUser();

	int word_count = CountWords(str);

	if (0 <= word_count)
		printf("The number of words in the given string is: %d.\n", word_count);
	else
		printf("Error occurred.\n");
	
	free(line);

	return 0;
}
