#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// created by Moti Goldstein
#ifndef TRUE    
#define TRUE    1
#define FALSE   0
#endif
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define WHITE   "\033[0;37m"

#define TEST_DESC_LENGTH 256
#define MAX_NUMBER_SIZE 22
#define MAX_SIZE 512
int testsCounter = 0;
int passedTestsCounter = 0;

typedef struct _test_case_big_nums_t{
    char bigNum1[MAX_NUMBER_SIZE];
    char bigNum2[MAX_NUMBER_SIZE];
    char expectedResult[MAX_NUMBER_SIZE];
    char description[TEST_DESC_LENGTH];
} test_case_big_nums;

typedef struct _test_case_sort_big_nums
{
    char* bigNumbers[MAX_SIZE];
    int N;
    char* expectedResult[MAX_SIZE];
    char description[MAX_SIZE];
} test_case_sort_big_nums;

void setColor(char color[]);
test_case_big_nums createTestBigNumbers(char bigNum1[], char bigNum2[] , char expectedResult[], char description[]);
test_case_sort_big_nums createTestSortBigNumbers(char* bigNumbers[], int N, char* expectedResult[], char description[]);
void runTestBigNumbers(test_case_big_nums testCase, char result[]);
void runTestSortBigNumbers(test_case_sort_big_nums, char* result[]);
void printSummary();

void setColor(char color[]){
    printf("%s", color);
}

void printSummary(){
    printf("------------\nsummary\n%d Test cases were checked, %d/%d are passed.\n------------\n", testsCounter, passedTestsCounter, testsCounter);
    if(passedTestsCounter == testsCounter){
        setColor(GREEN);
        printf("All tests passed.\n");
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
            printf("█");
        setColor(GREEN);
        for (i = 0; i < numOfGreenLines; i++)
            printf("█");
        setColor(WHITE);
        printf("\n");
    }
}
// new tester

test_case_big_nums createTestBigNumbers(char bigNum1[], char bigNum2[] , char expectedResult[], char description[]){
    test_case_big_nums retTestCase = { 0 };
    strcpy(retTestCase.bigNum1, bigNum1);
    strcpy(retTestCase.bigNum2, bigNum2);
    strcpy(retTestCase.expectedResult, expectedResult);
    strcpy(retTestCase.description, description);
    return retTestCase;
}
void runTestBigNumbers(test_case_big_nums testCase, char result[]){
    if (strcmp(testCase.expectedResult, result) == 0){
        setColor(GREEN);
        printf("Passed(%d): %s\n", testsCounter, testCase.description);
        passedTestsCounter++;
    }
    else{
        setColor(RED);
        printf("Failed(%d): %s, but function returned: %s \n", testsCounter, testCase.description, result);
    }
    setColor(WHITE);
    testsCounter++;
}

test_case_sort_big_nums createTestSortBigNumbers(char* bigNumbers[], int N, char* expectedResult[], char description[]){
    test_case_sort_big_nums retTestCase;

    *retTestCase.bigNumbers = (char*)calloc(N,sizeof(char)*MAX_NUMBER_SIZE);
    *retTestCase.expectedResult = (char*)calloc(N,sizeof(char)*MAX_NUMBER_SIZE);
    for(int i = 0; i < N; i++){
        strncpy(*(retTestCase.bigNumbers + i), *(bigNumbers + i), MAX_NUMBER_SIZE);
    }
        for(int i = 0; i < N; i++){
        strcpy(*(retTestCase.expectedResult + i), *(expectedResult + i));
    }
    retTestCase.N = N;
    strcpy(retTestCase.description, description);
    return retTestCase;
}
