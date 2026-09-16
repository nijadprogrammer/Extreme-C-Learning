// Extreme C
// chapter 1 exercise 10
// address incremental of integer and char

#include <stdio.h>

int main(int args, char** argv) {
    int var = 100;
    int *int_ptr = NULL;
    int_ptr = &var;
    char *char_ptr = NULL;
    char_ptr = (char*) &var;

    printf("Before arithmetic: int_ptr: %u, char_ptr: %u\n", 
           (unsigned int)int_ptr, (unsigned int)char_ptr);

    int_ptr++;
    char_ptr++;

    printf("After arithmetic: int_ptr: %u, char_ptr: %u\n", 
           (unsigned int)int_ptr, (unsigned int)char_ptr);

    return 0;
    
}
