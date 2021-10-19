
/*
I.D 318530136
I Believe that comments are needed where the code can't talk itself.
My efforts were invested in making readable code and write the minimum number of comments.
*/
#include <stdio.h>

#define MAX_DIGITS_IN_INT 10
#define TRUE    1
#define FALSE   0

#pragma region must-have functions declaration
int nextPrime(int num);
int isPalindrom(int num);
int containsNonPrimesDigitsOnly(int num);
int isSpecial(int num);
void printAllSpecial(int from, int to);
#pragma endregion

#pragma region optional functions declaration
int isPrime(int num);
#pragma endregion

#pragma region exercise
int nextPrime(int num){
    int i = num + 1;
    while(TRUE){
        if (isPrime(i) == TRUE)
            return i;
        i++;
    }
}

int isPalindrom(int num){
    if (num < 0) num *= -1;

    int digits[MAX_DIGITS_IN_INT];
    int digitsIndexer = 0, i = 0;

    while(num > 0){
        digits[digitsIndexer] = num % 10; 
        digitsIndexer++;
        num /= 10;
    }

    int numOfDigits = digitsIndexer;

    for (i = 0; i < numOfDigits / 2; i++)
        if (digits[i] != digits[numOfDigits - 1 - i])
            return FALSE;

    return TRUE;
}

int containsNonPrimesDigitsOnly(int num){
    if (num < 0) num *= -1;
    int currentDigit;

    while(num > 0){
        currentDigit = num % 10;
        if(isPrime(currentDigit) == TRUE)
            return FALSE;
            
        num /= 10;
    }

    return TRUE;
}

int isSpecial(int num){
    return isPalindrom(num) && containsNonPrimesDigitsOnly(num) && isPrime(num);
}

void printAllSpecial(int from, int to){
    if (to < from) return;
    int i;
    for(i = from; i <= to; i++)
        if (isSpecial(i))
            printf("%d\n", i);
        
}

int isPrime(int num){
    if (num < 2) return FALSE;
    int i;
    for (i = 2; i < num; i++)
        if (num % i == 0) 
            return FALSE;
    return TRUE;
}
#pragma endregion