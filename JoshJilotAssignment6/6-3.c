#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void f(float *a, int length, float *dest) {
    float prod = 1.0f;
    for (int i = 0; i < length; ++i) {
        if (a[i] != 0.0f) {
        prod *= a[i];
        }
    }
    *dest = prod;
}

void g(float *a, int length, float *dest) {
    float prod = 1.0f;
    for (int i = 0; i < length; ++i)
        prod *= a[i];
    *dest = prod;
    // Calling g(b) is more efficient than f(a) because you don't
    // need to spend time checking for 0s.
    // Calling g(c) is even more efficient because you don't even
    // need to multiply by one which takes time even without the
    // multiplication bcause it must run through the for loop more 
    // times.
}

float *createArray(int length) {
    float *a = (float *)malloc(length * sizeof(float));
    for (int i = 0; i < length; ++i) {
        // 50% chance that a[i] is 0.0f, random value on the range
        // [0.75, 1.25] otherwise.
        float r = rand()/(float)RAND_MAX;
        a[i] = r < 0.5f ? 0.0f : r + 0.26f;
    }
    return a;
}

int main() {
    // create array
    long length = 10000;
    long length_c = 10000;
    float *a = createArray(length);
    float result;

    // time runtime for f
    clock_t start1 = clock();
    for (int i = 0; i < 10000; i++) {
        f(a, length, &result);
    }
    clock_t end1 = clock();

    // print time
    double totalTime1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    printf("f runtime: %f\n", totalTime1);
    
    // copy a to b and replace 0s with 1s
    float *b = malloc(length*sizeof(float));
    for (int i = 0; i < length; i++) {
        b[i] = a[i];
        if (a[i] == 0.0f)
            b[i] = 1.0f;
    }

    // time runtime for g
    clock_t start2 = clock();
    for (int i = 0; i < 10000; i++) {
        g(b, length, &result);
    }
    clock_t end2 = clock();

    // print time
    double totalTime2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    printf("g runtime: %f\n", totalTime2);

    // create c (copy a and delete all 0s)
    float *c = malloc(length*sizeof(float));
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (a[i] != 0.0f) {
            c[j] = a[i];  // if a[i] val isn't 0 add to c
            }
        else {
            j--;  // otherwise keep c index (j) at current value
            length_c--;  // and shorten length for g call later
        }
        j++;  // incremement c index
    }

    // time runtime for g with c
    clock_t start3 = clock();
    for (int i = 0; i < 10000; i++) {
        g(c, length_c, &result);
    }
    clock_t end3 = clock();

    // print time
    double totalTime3 = ((double) (end3 - start3)) / CLOCKS_PER_SEC;
    printf("g runtime: %f\n", totalTime3);

    free(a);
    free(b);
    free(c);
    return 0;
}