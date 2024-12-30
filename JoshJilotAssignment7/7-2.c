#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ColorPoint {
    long a;
    long r;
    long g;
    long b;
};

void f(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[i][j].a;
            sum += points[i][j].r;
            sum += points[i][j].g;
            sum += points[i][j].b;
        }
    }
    *dest = sum;
    // mem read  - result - tag
    // [0][0].a  -  miss  -  0
    // [0][0].r  -  hit   -  0
    // [0][0].g  -  hit   -  0
    // [0][0].b  -  hit   -  0
    // [0][1].a  -  hit   -  0
    // [0][1].r  -  hit   -  0
    // [0][1].g  -  hit   -  0
    // [0][1].b  -  hit   -  0
    // Every 8 reads there will be a miss resulting in the
    // tag increasing by one. This pattern will continue.
}

void g(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[j][i].a;
            sum += points[j][i].r;
            sum += points[j][i].g;
            sum += points[j][i].b;
        }
    }
    *dest = sum;
    // mem read  - result - tag
    // [0][0].a  -  miss  -  0
    // [0][0].r  -  hit   -  0
    // [0][0].g  -  hit   -  0
    // [0][0].b  -  hit   -  0
    // [1][0].a  -  miss  -  2
    // [1][0].r  -  hit   -  2
    // [1][0].g  -  hit   -  2
    // [1][0].b  -  hit   -  2
    // Every 4 reads there will be a miss resulting in the
    // tag increasing by two and every 16 reads there will
    // be a miss resulting in the tag being reset to a different
    // value determined by j and i. Therefore the pattern demonstrated
    // here will not continue.
}

struct ColorPoint** create2DArray(int n) {
    // Array to hold a pointer to the beginning of each row
    struct ColorPoint **points = (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
    for (int i = 0; i < n; ++i) {
        // Array to hold each row
        points[i] = (struct ColorPoint *)malloc(n * sizeof(struct ColorPoint));
        for (int j = 0; j < n; ++j) {
            // Init the ColorPoint struct
            points[i][j].a = rand();
            points[i][j].r = rand();
            points[i][j].g = rand();
            points[i][j].b = rand();
        }
    }
    return points;
}

void free2DArray(struct ColorPoint** points, int n) {
    for (int i = 0; i < n; ++i) {
        free(points[i]);
    }
    free(points);
}

int main() {
    // allocate arrays
    struct ColorPoint** color_points = create2DArray(2048);
    long dest;

    // time runtime for f
    clock_t start1 = clock();
    for (int i=0; i<100; i++)
        f(color_points, 2048, &dest);
    clock_t end1 = clock();

    // print time
    double totalTime1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    printf("f runtime: %f\n", totalTime1);

    // time runtime for g
    clock_t start2 = clock();
    for (int i=0; i<100; i++)
        g(color_points, 2048, &dest);
    clock_t end2 = clock();

    // print time
    double totalTime2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    printf("g runtime: %f\n", totalTime2);

    // free arrays
    free2DArray(color_points, 2048);

    return 0;
    // f ran about twice as fast as g which makes sense because there
    // are about twice as many cache misses when g runs compared to when f runs.
}