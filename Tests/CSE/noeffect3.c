#include <stdio.h>
#include <stdlib.h>

int main() {
    int a;
    int b;
    int c;
    char *aa = (char *) &a;
    char *bb = (char *) &b;

    a = *aa + *bb + 2;
    c = *aa + *bb + 4;

    printf("Hello World!\n");
}
