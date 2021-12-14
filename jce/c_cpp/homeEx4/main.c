#include <stdio.h>
#include "StudentList.h"

int main(){
    int pt = 3;
    int* ptr = &pt;
    int* ptr2 = ptr;
    printf("%d\n", ptr2 == ptr);
    int p1 = 54;
    ptr = &p1;
    printf("%d\n", ptr2 == ptr);
    return 0;
}