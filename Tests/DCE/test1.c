#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = rand();
    int b = rand();

    // Dead Code
    a + 1;
    b + 2;
    a + b;

    printf("Hello World!\n");
}
