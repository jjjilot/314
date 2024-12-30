#include <stdio.h>

void printBytes(unsigned char *start, int len) {
    /*
    printBytes takes a pointer to an unsigned char as an input and an int 
    as the number of bytes to print for the input. It has no return value 
    and prints the first n number of bytes in start where n = len = number 
    of bytes used to store input type.
    */
    for (int i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void printInt(int x) {
    /* 
    Based on the output it appears as though my machine is big endian.
    */
    printBytes((unsigned char *) &x, sizeof(int));
}

void printFloat(float x) {
    /* 
    As observed in the outputs of my two examples the first byte mostly stores
    the exponent of the float so it is always used. The rest of the bytes are 
    mainly used for the mantissa so they will be greater when the number has a
    decimal or integer value that is difficult to create with powers of two.
    However, in cases such as my first example a decimal that perfectly factors
    into a power of two results in two empty bytes in the mantissa.
    */
    printBytes((unsigned char *) &x, sizeof(float));
}

int main()
{
    printInt(95);
    printInt(999999);

    printFloat(-91.5);
    printFloat(55555.987);

    return 0;
}