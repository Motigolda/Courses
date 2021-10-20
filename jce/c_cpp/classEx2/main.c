#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define EXIT_WORD "exit"
#define MAX_INPUT_SIZE 512

int getCharsValueSum(char str[], int strLength);

int main(){
    char userInput[MAX_INPUT_SIZE] = {1,2,3};
    int asciiSum = 0;
    while(strcmp(EXIT_WORD, userInput) != 0){
        printf("Enter string [maximum length:%d, enter %s to exit]: ", MAX_INPUT_SIZE, EXIT_WORD);
        scanf("%s", userInput);
        asciiSum = getCharsValueSum(userInput, MAX_INPUT_SIZE);
        if (strcmp(EXIT_WORD, userInput) == 0) return 0;
        printf("%d\n", asciiSum);
    }
    return 0;
}

int getCharsValueSum(char str[], int strLength){
    int asciiSum = 0;
    int i = 0;
    for (i = 0; i < strLength; i++){
        if (str[i] == '\0') break;
        asciiSum += str[i];
    }
    return asciiSum;
}


