#include <stdlib.h>
#include <stdio.h>

unsigned int combine (unsigned int x, unsigned int y)
{
    // Use bitmasks to isolate last three bytes of x and first byte of y
    unsigned int x_leading = x & 0xFFFFFF00;
    unsigned int y_ending = y & 0x000000FF;

    // return combination of these isolated bytes
    return x_leading | y_ending;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        unsigned int x = strtoul(argv[1], NULL, 16);
        unsigned int y = strtoul(argv[2], NULL, 16);
        printf("combine(%X, %X): %X", x, y, combine(x, y));
    } else {
        // TODO - your test cases go here!
        printf("=====Testing combine function=====\n");
        printf("Should return: 0x12345600 \nActually returned: 0x%X \n", combine(0x12345678, 0xABCDEF00));
        printf("Should return: 0xABCDEF78 \nActually returned: 0x%X \n", combine(0xABCDEF00, 0x12345678));
        printf("\n");
    }
    return 0;
}