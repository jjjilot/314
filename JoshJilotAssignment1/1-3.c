#include <stdlib.h>
#include <stdio.h>

int oddIndexBit(unsigned int x)
{
    // Each line compares the current x bits to the first half of x bits.
    // After four lines the remaining two bits represent if there were any odd or even bits.
    x = x | (x >> 16);
    x = x | (x >> 8);
    x = x | (x >> 4);
    x = x | (x >> 2);
    // Shifting x right one bit leaves only the bit representing the presence of any odd bits.
    x = x >> 1;
    // Returning x & 1 isolates the bit that identifies the presense of odd bits.
    return x & 1;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        unsigned int x = strtoul(argv[1], NULL, 16);
        printf("oddIndexBit(%X): %X", x, oddIndexBit(x));
    } else {
        // TODO - your test cases go here!
        printf("=====Testing oddIndexBit function=====\n");
        printf("Should return: 0 \nActually returned: %d \n", oddIndexBit(0x1));
        printf("Should return: 1 \nActually returned: %d \n", oddIndexBit(0x2));
        printf("Should return: 1 \nActually returned: %d \n", oddIndexBit(0x3));
        printf("Should return: 0 \nActually returned: %d \n", oddIndexBit(0x4));
        printf("Should return: 1 \nActually returned: %d \n", oddIndexBit(0xFFFFFFFF));
        printf("Should return: 1 \nActually returned: %d \n", oddIndexBit(0xAAAAAAAA));
        printf("Should return: 0 \nActually returned: %d \n", oddIndexBit(0x55555555));
        printf("\n");
    }
    return 0;
}