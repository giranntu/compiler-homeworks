#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[10];
    int b[10];
    int c;

    a[5] = (a[5] + b[5]) + 2;
    c = a[5] + b[5] + 4;

    printf("Hello World!\n");
}
