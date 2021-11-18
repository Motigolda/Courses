#include <stdio.h>
#include <string.h>
#include "testerEx2.h"
#include "main.c"
void testBigNums(){
    test_case_big_nums simpleFlow;
    char resultSimpleFlow[MAX_NUMBER_SIZE] = { 0 };
    simpleFlow = createTestBigNumbers("123", "1", "124", "simpleFlow 123 + 1 = 124");
    addBigNumbers(simpleFlow.bigNum1, simpleFlow.bigNum2, resultSimpleFlow);

    test_case_big_nums littleNumbersFlow;
    char bigNum1Little[] = "4";
    char bigNum2Little[] = "6";
    char expectedResultLittleNumbersFlow[] = "10";
    char descriptionLittleNumbersFlow[] = "littleNumbersFlow 4 + 6 = 10";
    char resultLittleNumbersFlow[MAX_NUMBER_SIZE] = { 0 };
    littleNumbersFlow = createTestBigNumbers(bigNum1Little, bigNum2Little, expectedResultLittleNumbersFlow, descriptionLittleNumbersFlow);
    addBigNumbers(bigNum1Little, bigNum2Little, resultLittleNumbersFlow);

    test_case_big_nums first15LenSec10Len;
    char bigNum1Len15Len10[] = "123451234512345";
    char bigNum2Len15Len10[] = "1234512345";
    char expectedResult15Len10Len[] = "123452469024690";
    char description15Len10Len[] = "first 15 length, second 10 length";
    char result15Len10Len[MAX_NUMBER_SIZE] = { 0 };
    first15LenSec10Len = createTestBigNumbers(bigNum1Len15Len10, bigNum2Len15Len10, expectedResult15Len10Len, description15Len10Len);
    addBigNumbers(bigNum1Len15Len10, bigNum2Len15Len10, result15Len10Len);

    test_case_big_nums first10LenSec15Len;
    char bigNum1Len10Len15[] = "9436354362";
    char bigNum2Len10Len15[] = "967453589076331";
    char expectedResult10Len15Len[] = "967463025430693";
    char description10Len15Len[] = "first 10 length, second 15 length";
    char result10Len15Len[MAX_NUMBER_SIZE];
    first10LenSec15Len = createTestBigNumbers(bigNum1Len10Len15, bigNum2Len10Len15, expectedResult10Len15Len, description10Len15Len);
    addBigNumbers(bigNum1Len10Len15, bigNum2Len10Len15, result10Len15Len);

    test_case_big_nums notDigits;
    char resultNotDigits[MAX_NUMBER_SIZE];
    notDigits = createTestBigNumbers("12344","moti","error","Letters");
    addBigNumbers(notDigits.bigNum1, notDigits.bigNum2, resultNotDigits);

    test_case_big_nums carryOn;
    char resultCarryOn[MAX_NUMBER_SIZE];
    carryOn = createTestBigNumbers("999999999", "999999999", "1999999998","Is carry works");
    addBigNumbers(carryOn.bigNum1, carryOn.bigNum2, resultCarryOn);

    test_case_big_nums zeros;
    char resultZeros[MAX_NUMBER_SIZE];
    zeros = createTestBigNumbers("0", "0", "0", "Zeros");
    addBigNumbers(zeros.bigNum1, zeros.bigNum2, resultZeros);

    test_case_big_nums oneItemZero;
    char resultOneItemZero[MAX_NUMBER_SIZE];
    oneItemZero = createTestBigNumbers("123", "0", "123", "One item zero");
    addBigNumbers(oneItemZero.bigNum1, oneItemZero.bigNum2, resultOneItemZero);

    runTestBigNumbers(simpleFlow, resultSimpleFlow);
    runTestBigNumbers(littleNumbersFlow, resultLittleNumbersFlow);
    runTestBigNumbers(first15LenSec10Len, result15Len10Len);
    runTestBigNumbers(first10LenSec15Len, result10Len15Len);
    runTestBigNumbers(notDigits, resultNotDigits);
    runTestBigNumbers(carryOn, resultCarryOn);
    runTestBigNumbers(zeros, resultZeros);
    runTestBigNumbers(oneItemZero, resultOneItemZero);
}

void testSortBigNums(){
    char* bigNums[] = {"55555555555","123", "1234", "1","123444"};
    printCharMat(bigNums, 5);
    sortBigNumbers(bigNums, 5);
    printCharMat(bigNums, 5);

}
int main(){

    testSortBigNums();

    printSummary();
    return 0;
}