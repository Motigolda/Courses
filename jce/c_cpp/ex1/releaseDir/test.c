#include <stdio.h>
#include <string.h>
#include "main.h"

#define TEST_DESC_LENGTH 256
// testing code
// text colors
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define WHITE   "\033[0;37m"
#ifndef TRUE    
#define TRUE    1
#define FALSE   0
#endif
typedef struct{
    int input;
    int expectedValue;
    int actualValue;
    char description[TEST_DESC_LENGTH];
} TEST_CASE;
int testsCounter = 0;
int passedTestsCounter = 0;
void testCase(TEST_CASE);
void setColor(char color[]);
void setTestData(TEST_CASE *c, const int input, const int exceptedValue, const int actualValue, char description[]);
void printAllSpecial(int from, int to);
int main(){
    printf("------------\nTests for Home Exercise 1 in Shay Tavor c/c++ course------------\n\n\n");
    #pragma region isPrime Tests
    printf("------------\ntests of isPrime(int num)\n------------\n");
    TEST_CASE negativeNumber;
    TEST_CASE zero;
    TEST_CASE primeNumber;
    TEST_CASE nonPrimeNumber;
    TEST_CASE anotherPrime;
    TEST_CASE anotherNonPrime;
    TEST_CASE theNumber29IsAPrime;
    setTestData(&negativeNumber, -123, FALSE, isPrime(-123), "negative number can't be prime");
    setTestData(&zero, 0, FALSE, isPrime(0), "zero is not a prime");
    setTestData(&primeNumber, 23, TRUE, isPrime(23), "23 is a Prime");
    setTestData(&nonPrimeNumber, 88, FALSE, isPrime(88), "88 is not a Prime number");
    setTestData(&anotherPrime, 17, TRUE, isPrime(17), "17 is a Prime");
    setTestData(&theNumber29IsAPrime, 29, TRUE, isPrime(29), "29 is a prime");
    testCase(negativeNumber);
    testCase(zero);
    testCase(primeNumber);
    testCase(nonPrimeNumber);
    testCase(anotherPrime);
    testCase(theNumber29IsAPrime);
    #pragma endregion
    
    #pragma region nextPrime Tests
    TEST_CASE nextOf0Is2;
    TEST_CASE nextOf6Is7;
    TEST_CASE nextOf222Is223;
    TEST_CASE nextOf543Is547;
    TEST_CASE nextOf1733Is1741;
    TEST_CASE nextOfminus334Is2;
    printf("------------\ntests of nextPrime(int num)\n------------\n");
    setTestData(&nextOfminus334Is2, -334, 2, nextPrime(-334),   "the next prime after -334 is 2");
    setTestData(&nextOf0Is2, 0, 2, nextPrime(0),                "The next prime after 0 is 2");
    setTestData(&nextOf6Is7, 6, 7, nextPrime(6),                "The next prime after 6 is 7");
    setTestData(&nextOf222Is223, 222, 223, nextPrime(222),      "The next prime after 222 is 223");
    setTestData(&nextOf543Is547, 543, 547, nextPrime(543),      "The next prime after 543 is 547");
    setTestData(&nextOf1733Is1741, 1733, 1741, nextPrime(1733), "The next prime after 1733 is 1741");
    setTestData(&nextOfminus334Is2, -334, 2, nextPrime(-334),  "The next prime after -334 is 2");
    testCase(nextOf0Is2);
    testCase(nextOf6Is7);
    testCase(nextOf222Is223);
    testCase(nextOf543Is547);
    testCase(nextOf1733Is1741);
    testCase(nextOfminus334Is2);
    #pragma endregion

    #pragma region isPalindrom Tests
    printf("------------\ntests of isPalindrom(int num)\n------------\n");
    // test cases
    TEST_CASE theNumber123321IsAPalindrom;
    TEST_CASE theNumber12334IsNotAPalindrom;
    TEST_CASE theNumber3332IsNotAPalindrom;
    TEST_CASE theNumber7845487isAPalindrom;
    TEST_CASE theNumber981232189isAPalindrom;
    TEST_CASE theNumber1IsAPalindrom;
    TEST_CASE theNumber11IsAPalindrom;
    TEST_CASE theNumberMinus11IsAPalindrom;
    // test set data
    setTestData(&theNumber123321IsAPalindrom, 123321, TRUE, isPalindrom(123321),            "The number 123321 is a palindrom");
    setTestData(&theNumber12334IsNotAPalindrom, 12334, FALSE, isPalindrom(12334),           "The number 12334 is not a palindrom");
    setTestData(&theNumber3332IsNotAPalindrom, 3332, FALSE, isPalindrom(3332),              "The number 3332 is not a palindrom");
    setTestData(&theNumber7845487isAPalindrom, 7845487, TRUE, isPalindrom(7845487),         "The number 7845487 i a palindrom");
    setTestData(&theNumber981232189isAPalindrom, 981232189, TRUE, isPalindrom(981232189),   "The number 981232189 is a palindrom");
    setTestData(&theNumber1IsAPalindrom, 1, TRUE, isPalindrom(1),                           "The number 1 is a palindrom");
    setTestData(&theNumber11IsAPalindrom, 11, TRUE, isPalindrom(11),                        "The number 11 is a palindrom");
    setTestData(&theNumberMinus11IsAPalindrom, -11, TRUE, isPalindrom(-11),                 "The number -11 is a palindrom");
    // test run
    testCase(theNumber123321IsAPalindrom);
    testCase(theNumber12334IsNotAPalindrom);
    testCase(theNumber3332IsNotAPalindrom);
    testCase(theNumber7845487isAPalindrom);
    testCase(theNumber981232189isAPalindrom);
    testCase(theNumber1IsAPalindrom);
    testCase(theNumber11IsAPalindrom);
    testCase(theNumberMinus11IsAPalindrom);
    #pragma endregion
    
    #pragma region containsNonPrimesDigitsOnly Tests
    printf("------------\ntests of containsNonPrimesDigitsOnly(int num)\n------------\n");
    // test cases
    TEST_CASE number69641IsOk;
    TEST_CASE number269641IsNotOk;
    TEST_CASE number28829IsNotOk;
    TEST_CASE number0IsOk;
    TEST_CASE numberMinus11994IsOk;
    setTestData(&number69641IsOk, 69641, TRUE, containsNonPrimesDigitsOnly(69641), "The number 69641 is non primes only");
    setTestData(&number269641IsNotOk, 269641, FALSE, containsNonPrimesDigitsOnly(269641), "The number 269641 contains primes");
    setTestData(&number28829IsNotOk, 28829, FALSE, containsNonPrimesDigitsOnly(28829), "The number 28829 contains primes");
    setTestData(&number0IsOk, 0, TRUE, containsNonPrimesDigitsOnly(0), "The number 0 is non primes only");
    setTestData(&numberMinus11994IsOk, -11994, TRUE, containsNonPrimesDigitsOnly(-11994), "The number -11994 is non primes number");
    testCase(number69641IsOk);
    testCase(number269641IsNotOk);
    testCase(number28829IsNotOk);
    testCase(number0IsOk);
    testCase(numberMinus11994IsOk);
    #pragma endregion
    
    #pragma region isSpecial Tests
    printf("------------\ntests of isSpecial(int num)\n------------\n");
    // [11, 101, 181, 191, 919]
    TEST_CASE number11IsSpecial;
    TEST_CASE number181IsSpecial;
    TEST_CASE number101IsSpecial;
    TEST_CASE number191IsSpecial;
    TEST_CASE number919IsSpecial;
    TEST_CASE number29IsNotSpecial;
    TEST_CASE number902IsNotSpecial;
    TEST_CASE number9919IsNotSpecial;
    TEST_CASE numberMinus1IsNotSpecial;
    setTestData(&number11IsSpecial, 11,TRUE,isSpecial(11),              "The number 11 is special");
    setTestData(&number181IsSpecial,181,TRUE,isSpecial(181),            "The number 181 is special");
    setTestData(&number101IsSpecial,101,TRUE,isSpecial(101),            "The number 101 is special");
    setTestData(&number191IsSpecial,191,TRUE,isSpecial(191),            "The number 191 is special");
    setTestData(&number919IsSpecial,919,TRUE,isSpecial(919),            "The number 919 is special");
    setTestData(&number29IsNotSpecial,29,FALSE,isSpecial(29),           "The number 29 is not special");
    setTestData(&number902IsNotSpecial,902,FALSE,isSpecial(902),        "The number 902 is not special");
    setTestData(&number9919IsNotSpecial,9919,FALSE, isSpecial(9919),    "The number 9919 is not special");
    setTestData(&numberMinus1IsNotSpecial, -123, FALSE, isSpecial(-123),"The number -123 is not spceial");
    testCase(number11IsSpecial);
    testCase(number181IsSpecial);
    testCase(number101IsSpecial);
    testCase(number191IsSpecial);
    testCase(number919IsSpecial);
    testCase(number29IsNotSpecial);
    testCase(number902IsNotSpecial);
    testCase(number9919IsNotSpecial);
    testCase(numberMinus1IsNotSpecial);
    #pragma endregion
    
    // TODO: printAllSpecial Tests

    printf("------------\nsummary\n%d Test cases were checked, %d/%d are passed.\n------------\n", testsCounter, passedTestsCounter, testsCounter);
    if(passedTestsCounter == testsCounter){
        setColor(GREEN);
        printf("All tests were passed.\n");
        setColor(WHITE);
    }
    else{
        double testsPassed = passedTestsCounter,
            numOfTests = testsCounter;
        
        int numOfRedLines = ((numOfTests - testsPassed) / numOfTests) * 50;
        int numOfGreenLines = ((testsPassed) / numOfTests) * 50;
        setColor(RED);
        int i = 0;
        for (i = 0; i < numOfRedLines; i++)
            printf("▮");
        setColor(GREEN);
        for (i = 0; i < numOfGreenLines; i++)
            printf("▮");
        setColor(WHITE);
        printf("\n");
    }
    printAllSpecial(100, 16062);
}
void testCase(TEST_CASE c){
    if (c.actualValue == c.expectedValue){
        setColor(GREEN);
        printf("Passed(%d): %s\n", testsCounter, c.description);
        passedTestsCounter++;
    }
    else{
        setColor(RED);
        printf("Failed(%d): %s, but function returned: %d \n", testsCounter, c.description, c.actualValue);
    }
    setColor(WHITE);
    testsCounter++;
}
void setColor(char color[]){
    printf("%s", color);
}
void setTestData(TEST_CASE *c, const int input, const int exceptedValue, const int actualValue, char description[]){
    c->input = input;
    c->expectedValue = exceptedValue;
    c->actualValue = actualValue;
    strcpy(c->description, description);
}