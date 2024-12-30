#include <stdlib.h>
#include <stdio.h>

unsigned int mask(int n)
{
    unsigned int outp = 0xFFFFFFFF;  // create mask of all 1s
    outp >>= (32-n);  // shift mask by n less than its size, turning off all but the least significant n bits 
    return outp;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int n = strtol(argv[1], NULL, 10);
        printf("mask(%d): %X", n, mask(n));
    } else {
        // TODO - your test cases go here!
        printf("=====Testing mask function=====\n");
        printf("Show me: 1 \nActually returned: %X \n", mask(1));
        printf("Show me: 3 \nActually returned: %X \n", mask(2));
        printf("Show me: 7 \nActually returned: %X \n", mask(3));
        printf("Show me: 1F \nActually returned: %X \n", mask(5));
        printf("Show me: FF \nActually returned: %X \n", mask(8));
        printf("Show me: FFFF \nActually returned: %X \n", mask(16));
        printf("Show me: 7FFFFFFF \nActually returned: %X \n", mask(31));
        printf("\n");
    }
    return 0;
}