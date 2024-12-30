#include <stdlib.h>
#include <stdio.h>

// No stack operations
long iterativeFact(long x) {
    long outp = 1;
    for (int i=x; i>1; i--)
        outp *= i;
    return outp;
}

// Two stack operations per call (excluding base case):
//    -push incomplete function calls to stack
//    -pop function calls from stack once base case is reached
long recursiveFact(long x) {
    if (x<2) return 1;
    return recursiveFact(x-1) * x;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        long x = strtol(argv[1], NULL, 10);
        printf("iterativeFact(%ld): %ld\n", x, iterativeFact(x));
        printf("recursiveFact(%ld): %ld\n", x, recursiveFact(x));
    } else {
        // TODO - add any hardcoded test cases you'd like here!
        printf("iter 1: %ld\n", iterativeFact(0));
        printf("iter 1: %ld\n", iterativeFact(1));
        printf("iter 120: %ld\n", iterativeFact(5));
        printf("recur 1: %ld\n", recursiveFact(0));
        printf("recur 1: %ld\n", recursiveFact(1));
        printf("recur 120: %ld\n", recursiveFact(5));
    }
    return 0;
}