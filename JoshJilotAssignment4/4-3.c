#include <stdlib.h>
#include <stdio.h>
/*
.L3:
        movq    (%rax), %rcx    // long tmp1 = *rp;
        movq    (%rdx), %rsi    // long tmp2 = *cp;
        movq    %rsi, (%rax)    // *rp = tmp2;
        movq    %rcx, (%rdx)    // *cp = tmp1;
        addq    $8, %rax        // rp += 1;
        addq    $32, %rdx       // cp += 4;
        cmpq    %r9, %rax       // j < i;
        jne     .L3
*/

void transpose(long a[4][4]) {
    for (long i = 0; i < 4; ++i) {
        for (long j = 0; j < i; ++j) {
            long t1 = a[i][j];
            long t2 = a[j][i];
            a[i][j] = t2;
            a[j][i] = t1;
        }
    } 
}

void transposeOpt(long a[4][4]) {
    for (long i = 0; i < 4; ++i) {
        long *rp = &a[i][0];
        long *cp = &a[0][i];
        for (long j = 0; j < i; ++j) {
            // TODO - swap data at rp, cp pointers, increment rp, cp
            // (as shown in the optimized x86-64 code above)
            long tmp1 = *rp;
            long tmp2 = *cp;
            *rp = tmp2;
            *cp = tmp1;
            rp += 1;
            cp += 4;
        }
    }
}

void print(long a[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j =  0; j < 4; ++j) {
        printf("%ld ", a[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 17) {
        long a[4][4];
        long b[4][4];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                a[i][j] = strtol(argv[i * 4 + j + 1], NULL, 10);
                b[i][j] = a[i][j];
            }
        }
        transpose(a);
        printf("transpose(a)\n");
        print(a);
        transposeOpt(b);
        printf("trasnposeOpt(b)\n");
        print(b);
    } else {
        // TODO - add any hardcoded test cases you'd like here!
    }
    return 0;
}