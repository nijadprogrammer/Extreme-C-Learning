#include <stdio.h>

void print_bytes(void *data, size_t length) {
    char delim = ' ';
    unsigned char *ptr = NULL;
    ptr = data;
    for(size_t i=0; i<length; i++) {
        printf("%c 0x%x", delim, *ptr);
        delim = ',';
        *ptr++;
    }
    printf("\n");
}

int main(int args, char** argv) {
    int a = 9;
    double b = 18.5;

    print_bytes(&a, sizeof(int));
    print_bytes(&b, sizeof(double));
}
