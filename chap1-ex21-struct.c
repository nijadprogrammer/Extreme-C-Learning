#include <stdio.h>

struct sample_t {
    char first;
    char second;
    char third;
    short fourth;
};

void print_size(struct sample_t *data) {
    printf("Size is %lu bytes\n", sizeof(*data));
}

void print_bytes(struct sample_t *data) {
    unsigned char *ptr = (unsigned char*)data;
    for(int i=0; i<sizeof(*data); i++, ptr++) {
        printf("Byte %d is %d\n", i+1, (unsigned int)*ptr);
    }
}

int main(int args, char** argv) {
    struct sample_t var;
    var.first = 'A';
    var.second = 'B';
    var.third = 'C';
    var.fourth = 756;

    print_size(&var);
    print_bytes(&var);
    
    return 0;
    
}
