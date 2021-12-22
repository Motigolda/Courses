// I.D 318530136
#include <stdio.h>
#define MAX_INT_NUM_OF_DIGITS 10
#ifndef TRUE    
#define TRUE    1
#define FALSE   0
#endif
#ifndef _MAIN_H
#define _MAIN_H
// must-have functions
int nextPrime(int num);
int isPalindrom(int num);
int containsNonPrimesDigitsOnly(int num);
int isSpecial(int num);
void printAllSpecial(int from, int to);
// opitional functions
int isPrime(int num);
#endif
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
    int digits[MAX_INT_NUM_OF_DIGITS];
    int numOfDigits = 0, i = 0;
    while(num > 0){
        digits[numOfDigits] = num % 10; 
        numOfDigits++;
        num /= 10;
    }
    for (i = 0; i < numOfDigits / 2; i++)
        if (digits[i] != digits[numOfDigits - 1 - i])
            return FALSE;

    return TRUE;
}

int containsNonPrimesDigitsOnly(int num){
    if (num < 0) num *= -1;
    while(num > 0){
        if(isPrime(num % 10) == TRUE)
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
