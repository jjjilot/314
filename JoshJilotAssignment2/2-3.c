#include <stdlib.h>
#include <stdio.h>

int le(float x, float y) {
    unsigned int ux = *((unsigned int*) &x); // convert x raw bits
    unsigned int uy = *((unsigned int*) &y); // convert y raw bits
    unsigned int sx = ux >> 31; // extract sign bit of ux
    unsigned int sy = uy >> 31; // extract sign bit of uy   
    ux &= 0x7FFFFFFF; // drop sign bit of ux
    uy &= 0x7FFFFFFF; // drop sign bit of uy
    // TODO: return using sx, sy, ux, uy
    // return statement has cases for all combinations of signs and for when both are zero
    return (sx > sy) | ((sx == 0) & (sy == 0) & (ux <= uy)) | 
    ((ux == 0) & (uy == 0)) | ((sx == 1) & (sy == 1) & (ux >= uy));
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        float x = strtof(argv[1], NULL);
        float y = strtof(argv[2], NULL);
        printf("le(%f, %f): %d", x, y, le(x, y));
    } else {
        // TODO - your test cases go here!
        printf("=====Testing le function (hon hon hon)=====\n");
        printf("Show me: 1 \nActually returned: %d \n", le(0.0f, 0.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(-0.0f, 0.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(0.0f, -0.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(-0.0f, -0.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(1.0f, 1.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(-1.0f, 1.0f));
        printf("Show me: 0 \nActually returned: %d \n", le(1.0f, -1.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(-1.0f, -1.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(-1.0f, 0.0f));
        printf("Show me: 0 \nActually returned: %d \n", le(0.0f, -1.0f));
        printf("Show me: 0 \nActually returned: %d \n", le(1.0f, 0.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(0.0f, 1.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(1.0f, 2.0f));
        printf("Show me: 0 \nActually returned: %d \n", le(2.0f, 1.0f));
        printf("Show me: 0 \nActually returned: %d \n", le(-1.0f, -2.0f));
        printf("Show me: 1 \nActually returned: %d \n", le(-2.0f, -1.0f));
        printf("\n");
    }
    return 0;
}