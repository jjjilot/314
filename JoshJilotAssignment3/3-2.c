#include <stdlib.h>
#include <stdio.h>
/*
%rdi: x
%rsi: y
%rdx: z

movq    %rdx, %rax
subq    %rsi, %rax  // z -= y
imulq   %rax, %rdi  // x *= z
orq     %rdi, %rax  // z |= x
ret                 // return z
*/
long f(long x, long y, long z)
{
    z -= y;
    x *= z;
    z |= x;
    return z;
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        long x = strtol(argv[1], NULL, 10);
        long y = strtol(argv[2], NULL, 10);
        long z = strtol(argv[3], NULL, 10);
        printf("f(%ld, %ld, %ld): %ld\n", x, y, z, f(x, y, z));
    } else {
        // TODO - add any hardcoded test cases you'd like here!
        printf("%ld\n", f(1, 2, 4));
        printf("%ld\n", f(3, 5, 7));
        printf("%ld\n", f(10, 20, 40));
        printf("%ld\n", f(30, 50, 70));
        printf("%ld\n", f(30, 50, -70));
    }
    return 0;
}