#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = rand();
    int b = rand();
    int c;

    // Dead Code
    a = a + 1;
    b = b + 2;
    c = a + b;

    printf("Hello World!\n");
}
