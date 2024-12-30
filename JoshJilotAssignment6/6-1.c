#include <stdio.h>
#include <stdlib.h>

long f(long a, long b, long c, long d, long n) {
    long result = 0;
    long ab = a*b;
    // instead of multiplying cd by i we note that i increases 
    // by 2 each time and add 2cd to this term each pass
    long inc = 0; 
    long cd2 = c*d*2;
    for (long i = 0; i < n; i += 2) {
        for (long j = 0; j < n; j += 2) {
            // result += a * b + i * c * d + j;
            result += ab + inc + j;  // sum all terms
        }
        inc += cd2;  // adding 2cd to this term
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc == 6) {
        long a = strtol(argv[1], NULL, 10);
        long b = strtol(argv[2], NULL, 10);
        long c = strtol(argv[3], NULL, 10);
        long d = strtol(argv[4], NULL, 10);
        long e = strtol(argv[5], NULL, 10);
        printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", a, b, c, d, e, f(a, b, c, d, e));
    } else {
        // TODO - your test cases go here!
        printf("252: %ld\n", f(1, 2, 3, 4, 5));
        printf("432: %ld\n", f(2, 3, 4, 5, 6));
        printf("30: %ld\n", f(6, 5, 4, 3, 2));
        printf("20: %ld\n", f(5, 4, 3, 2, 1));
    }
    return 0;
}