#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[10];
    int b[10];
    int c;

    c = (a[5] + b[5]) + 2 + (((char *)a)[5] + ((char *)b)[5]);

    printf("Hello World!\n");
}
