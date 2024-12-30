#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inner(float *u, float *v, int length, float *dest) {
    float sum = 0.0f;
    for (int i = 0; i < length; ++i) {
        sum += u[i] * v[i];
    }
    *dest = sum;
    // Results indicated that inner2 was about 2-8 times faster than inner and 
    // inner3 was a little less than twice as fast as inner2. This makes
    // sense based on what we have learned about loop unrolling because each 
    // iteration decreases the number of times the loops restart significantly. The
    // limiting factors are the time it takes to multiply each value and the 
    // loop that deals with remainders which must iterate by one each time. I
    // noted that if I made the remainder loop trigger more often (by terminating
    // the primary loop earlier) it greatly increased the runtime making inner3
    // significantly slower than inner2.
}


void inner2(float *u, float *v, int length, float *dest) {
    // create parallel accumulators
    float sum1 = 0.0f;
    float sum2 = 0.0f;
    float sum3 = 0.0f;
    float sum4 = 0.0f;
    int i = 0;
    for (; i < length-4; i+=4) {
        // add to each accumulator
        sum1 += u[i] * v[i];
        sum2 += u[i+1] * v[i+1];
        sum3 += u[i+2] * v[i+2];
        sum4 += u[i+3] * v[i+3];
    }
    // deal with remaining elements if length is not evenly divisible by 4
    for (; i < length; i++) {
        sum1 += u[i] * v[i];
    }
    // sum all accumulators
    *dest = sum1 + sum2 + sum3 + sum4;
}

void inner3(float *u, float *v, int length, float *dest) {
    // create parallel accumulators
    float sum1 = 0.0f;
    float sum2 = 0.0f;
    float sum3 = 0.0f;
    float sum4 = 0.0f;
    float sum5 = 0.0f;
    float sum6 = 0.0f;
    float sum7 = 0.0f;
    float sum8 = 0.0f;
    int i = 0;
    for (; i < length-8; i+=4) {
        // add to each accumulator
        sum1 += u[i] * v[i];
        sum2 += u[i+1] * v[i+1];
        sum3 += u[i+2] * v[i+2];
        sum4 += u[i+3] * v[i+3];
        sum5 += u[i+4] * v[i+4];
        sum6 += u[i+5] * v[i+5];
        sum7 += u[i+6] * v[i+6];
        sum8 += u[i+7] * v[i+7];
    }
    // deal with remaining elements if length is not evenly divisible by 8
    for (; i < length; i++) {
        sum1 += u[i] * v[i];
    }
    // sum all accumulators
    *dest = sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7 + sum8;
}

float *createArray(int length) {
    float *a = (float *)malloc(length * sizeof(float));
    for (int i = 0; i < length; ++i) {
        a[i] = rand()/(float)RAND_MAX;
    }
    return a;
}

int main(){
    // create arrays
    float *array1 = createArray(100000);
    float *array2 = createArray(100000);
    float result;

    // time first implimentation
    clock_t start1 = clock();
    for (int i = 0; i < 10000; i++) {
        inner(array1, array2, 100000, &result);
    }
    clock_t end1 = clock();
    
    // print time
    double totalTime1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    printf("Inner time: %f\n", totalTime1);

    // time first implimentation
    clock_t start2 = clock();
    for (int i = 0; i < 10000; i++) {
        inner2(array1, array2, 100000, &result);
    }
    clock_t end2 = clock();

    // print time
    double totalTime2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    printf("Inner2 time: %f\n", totalTime2);

    // time first implimentation
    clock_t start3 = clock();
    for (int i = 0; i < 10000; i++) {
        inner3(array1, array2, 100000, &result);
    }
    clock_t end3 = clock();

    // print time
    double totalTime3 = ((double) (end3 - start3)) / CLOCKS_PER_SEC;
    printf("Inner3 time: %f\n", totalTime3);
    return 0;

    free(array1);
    free(array2);
}