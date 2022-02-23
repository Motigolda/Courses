#include <stdio.h>
#include <stdlib.h>

#include "word_count.h"

int main(void){
	char *str = malloc(1);	
	
	GetInputLineFromUser(&str);

	if(str == NULL){
		printf("Error: cant get input from user.\n");
		exit(1);
	}

	int word_count = CountWords(str);

	if (0 <= word_count)
		printf("The number of words in the given string is: %d.\n", word_count);
	else
		printf("Error occurred.\n");
	
	free(str);

	return 0;
}
