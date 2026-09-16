#include <stdio.h>

//#define CONDITION

int main(int argc, char** argv) {
#ifdef CONDITION
        int i = 0;
        i++;
        printf("%d\n",i);
#endif
        int j=5;
        j++;
        printf("%d\n", j);

    return 0;
}
