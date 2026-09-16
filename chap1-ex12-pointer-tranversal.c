// Extreme C
// chapter 1 exercise 12

#include <stdio.h>

#define SIZE 5

int main(int args, char** argv) {

    int arr[SIZE];
    arr[0] = 2;
    arr[1] = 89;
    arr[2] = 30;
    arr[3] = 59;
    arr[4] = 71;

    int *ptr = NULL;
    ptr = &arr[0];

    while(1) {
        printf("%d\n", *ptr);

        if(ptr == &arr[SIZE-1]) {
            break;
        }
        ptr++;
    }

    return 0;
    
}
