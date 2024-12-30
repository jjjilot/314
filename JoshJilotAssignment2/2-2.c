#include <stdlib.h>
#include <stdio.h>

unsigned int extract (unsigned int x, int i)
{
    i <<= 3;  // Shift i to multiply by 8
    int outp = (x >> i) & 0xFF;  // Shift byte at i to beginning of word and set all other bits to 0
    int mask = (outp >> 7) & 1;  // Create mask by shifting most significant bit to beginning of word and remove all others
    mask = (mask << 31) >> 31;  // Shift mask all the way left and back to sign extend
    return (mask << 8) | outp;  // Clear least signification byte and fill with i byte again
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        unsigned int x = strtoul(argv[1], NULL, 16);
        int i = strtol(argv[2], NULL, 10);
        printf("extract(%X, %d): 0x%08X", x, i, extract(x, i));
    } else {
        // TODO - your test cases go here!
        printf("=====Testing extract function=====\n");
        printf("Show me: 0x00000078 \nActually returned: 0x%08X \n", extract(0x12345678, 0));
        printf("Show me: 0xFFFFFFCD \nActually returned: 0x%08X \n", extract(0xABCDEF00, 2));
        printf("\n");
    }
    return 0;
}