#include <stdlib.h>
#include <stdio.h>
/*
loop:
        movq    %rsi, %rcx
        movl    $2, %edx    // long mask = 2
        movq    $-1, %rax   // long result = -1
.L2:
        movq    %rdi, %r8
        andq    %rdx, %r8   // (mask & x)
        xorq    %r8, %rax   // result ^= (mask & x)
        salq    %cl, %rdx   // mask <<= y
        cmpq    $1, %rdx    // mask > 1
        jg      .L2
        ret                 // return result
*/

long loop(long x, long y) {
    long result = -1;
    for (long mask = 2; mask > 1; mask <<= y) {
        result ^= (mask & x);
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        long a = strtol(argv[1], NULL, 10);   
        long b = strtol(argv[2], NULL, 10);
        printf("loop(%ld, %ld): %ld\n", a, b, loop(a, b));
    } else {
        // TODO - add any hardcoded test cases you'd like here!
        printf("-1: %ld\n", loop(1,5));
        printf("-3: %ld\n", loop(2,4));
        printf("-3: %ld\n", loop(3,3));
        printf("-1: %ld\n", loop(4,2));
        printf("-5: %ld\n", loop(5,1));
    }
    return 0;
}