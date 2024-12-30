#include <stdlib.h>
#include <stdio.h>

unsigned int replace (unsigned int x, int i, unsigned char b)
{
    i = i << 3;  // Bit shift i to multiply by 8
    unsigned int outp = x & ~(0xFF << i);  // Use bitmask to change target bytes to 0s
    outp |= b << i;  // change 0s to b
    return outp;
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        unsigned int x = strtoul(argv[1], NULL, 16);
        int i = strtol(argv[2], NULL, 10);
        unsigned char b = (unsigned char)strtoul(argv[3], NULL, 16);
        printf("replace(%X, %d, %X): %X", x, i, b, replace(x, i, b));
    } else {
        // TODO - your test cases go here!
        printf("=====Testing replace function=====\n");
        printf("Should return: 0xAB345678 \nActually returned: 0x%X \n", replace(0x12345678, 3, 0xAB));
        printf("Should return: 0x123456AB \nActually returned: 0x%X \n", replace(0x12345678, 0, 0xAB));
        printf("\n");
    }
    return 0;
}