#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int length;
    int *dataPtr;
} IntArray;

IntArray* mallocIntArray(int length)
{
    IntArray* array = malloc(sizeof(IntArray));
    array->length = length;
    array->dataPtr = malloc(length*sizeof(int));
    return array;
}

void freeIntArray(IntArray *arrayPtr) 
{
    free(arrayPtr->dataPtr);
    free(arrayPtr);
}

void readIntArray(IntArray *array)
{
    char *ptr;
    char inp[10];
    for (int i=0; i<array->length; i++){
        printf("Enter int\n");
        fgets(inp, sizeof(inp), stdin);
        array->dataPtr[i] = strtol(inp, &ptr, 10);
        if (array->dataPtr[i] <= 0){
            printf("Invalid input\n");
            i--;
        }
    }
}

void swap(int *xp, int *yp)
{
    int tmp = *xp;
    *xp = *yp;
    *yp = tmp;
}

void sortIntArray(IntArray *array)
{
    // Concept and code inspired by https://www.geeksforgeeks.org/selection-sort/
    for (int i=0; i<array->length; i++){
        int min_idx = i;
        for (int j=i+1; j<array->length; j++)
            if (array->dataPtr[j]<array->dataPtr[min_idx])
                min_idx = j;
        if (min_idx != i)
            swap(&array->dataPtr[min_idx], &array->dataPtr[i]);
    }
}

void printIntArray(IntArray *array)
{
    printf("[ ");
    for (int i=0; i<array->length; i++)
    if (i==0)
        printf("%d", array->dataPtr[i]);
    else
        printf(", %d", array->dataPtr[i]);
    printf("]\n");
}

int main(int argc, char *argv[])
{
    // ChatGPT used to understand fgets and strtol
    char *ptr;
    long length;
    char inp[100];
    int prompt = 1;
    while (prompt == 1){
        printf("Enter length\n");
        fgets(inp, sizeof(inp), stdin);
        length = strtol(inp, &ptr, 10);
        if (length <= 0)
            printf("Invalid input\n");
        else
            prompt = 0;
    }

    IntArray *array = mallocIntArray((int)length);
    readIntArray(array);
    sortIntArray(array);
    printIntArray(array);
    freeIntArray(array);
    return 0;
}