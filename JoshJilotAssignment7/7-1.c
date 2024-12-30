#include <stdio.h>
#include <stdlib.h>

unsigned int getOffset(unsigned int address) {
    return 0xF & address;
}

unsigned int getTag(unsigned int address) {
    return 0xFFFFFFF & address >> 4;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        unsigned int a = strtoul(argv[1], NULL, 16);
        unsigned int o = getOffset(a);
        unsigned int t = getTag(a);
        printf("%x: offset: %x - tag: %x\n", a, o, t);
    } else {
        // TODO - your test cases go here!
        printf("0x12345678: offset: %d - tag: %x\n", getOffset(0x12345678), getTag(0x12345678));
        printf("0x87654321: offset: %d - tag: %x\n", getOffset(0x87654321), getTag(0x87654321));
    }
}