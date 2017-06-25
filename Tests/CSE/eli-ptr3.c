#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[10];
    int b[10];
    int c;

    c = (a[4] + b[4]) + 2 + (*((char*)&a[4]) + *((char*)&b[4]));

    printf("Hello World!\n");
}
