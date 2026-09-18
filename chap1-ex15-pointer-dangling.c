// exercise 15
// dangling-pointer --> shows segmentation fault

#include <stdio.h>

int* create_an_integer(int data) {
    int var = data;
    return &var;
}

int main(int args, char** argv) {
    int *ptr = NULL;
    ptr = create_an_integer(10);
    printf("%d\n", *ptr);
    return 0;
    
}
