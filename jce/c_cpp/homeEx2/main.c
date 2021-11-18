#include <stdio.h>
#include <string.h>
#include "main.h"

#define TRUE 1
#define FALSE 0
#define ASCII_DELTA 48
#define ERROR_STR "error"

void addBigNumbers(char first[], char second[], char result[]){

    int i = strlen(first) - 1; 
    int j = strlen(second) - 1;
    int k = 0;
    int carry = 0;
    int currentDigit1 = 0;
    int currentDigit2 = 0; 
    int addition = 0;
    int firstBigger = i > j ? TRUE : FALSE;

    while (i >= 0 && j >= 0){
        if(!isADigit(first[i]) || !isADigit(second[j]))
        {
            strcpy(result, ERROR_STR);
            return;
        }

        currentDigit1 = charToDigit(first[i]);
        currentDigit2 = charToDigit(second[j]);
        addition = currentDigit1 + currentDigit2 + carry;

        if(firstBigger)
            first[i] = digitToChar(addition % 10);
        else
            second[j] = digitToChar(addition % 10);

        carry = addition > 9 ? 1 : 0;
        --i;
        --j;
    }


    if(firstBigger){
        while(i >= 0){
            currentDigit1 = charToDigit(first[i]);
            addition = currentDigit1 + carry;
            carry = addition > 9 ? 1 : 0;
            first[i] = digitToChar(addition % 10);
            --i;
        }
    }
    else{
        while(j >= 0){
            currentDigit2 = charToDigit(second[j]);
            addition = currentDigit2 + carry;
            carry = addition > 9 ? 1 : 0;
            second[j] = digitToChar(addition % 10);
            --j;
        }
    }
    
    k = 0;
    if(carry == 1){
        result[0] = '1';
        k++;
    }

    if(firstBigger){
        while(k < (int)strlen(first) + carry){
            result[k] = first[k];
            ++k;
        }
        result[k] = 0;
    }
    else{
        while(k < (int)strlen(second) + carry){
            result[k] = second[k-carry];
            ++k;
        }
        result[k] = 0;
    }
}

void sortBigNumbers(char* bigNumbers[], int N){
    int i = 0;
    int j = 0;
    for(i = 0; i < N; i++){
        for (j = 0; j < N-1-i; j++){
            if(strlen(*(bigNumbers + j)) > strlen(*(bigNumbers + j + 1)))
                swapPointersInArray(bigNumbers, j, j+1);
        }
    }
}

int charToDigit(const char ch){
    return ch - ASCII_DELTA;
}
int isADigit(const char ch){
    return '0' <= ch && ch <= '9';
}
char digitToChar(const int digit){
    return digit + ASCII_DELTA;
}

void printCharMat(char* mat[], int N){
    for(int i = 0; i < N; i++)
        printf("%s\n", *(mat + i));
    printf("\n");
}

void swapPointersInArray(char* array[], int i, int j){
    char* temp = *(array + i);
    *(array + i) = *(array + j);
    *(array + j) = temp;
}