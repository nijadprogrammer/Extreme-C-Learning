// Example 24 Chapter 1
// struct, pointers and casting

#include <stdio.h>

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    point_t center;
    int radius;
} circle_t;

int main(int args, char** argv) {
    circle_t c;
    circle_t *ptr1 = &c;
    point_t *ptr2 = (point_t*)&c;
    int *ptr3 = (int*)&c;

    printf("ptr1: %p\n", (void*)ptr1);
    printf("ptr2: %p\n", (void*)ptr2);
    printf("ptr3: %p\n", (void*)ptr3);

    return 0;
    
}
