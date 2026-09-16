#include <stdio.h>

#define add(a,b) a + b //macro

int main (int c,int d) {
    int x = 5;
    int y = 10;
    int z = add(x,y);

    printf("%d\n", z);
    return 0;
    
}
