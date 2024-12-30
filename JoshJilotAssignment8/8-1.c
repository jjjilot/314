#include <stdio.h>
#include <stdlib.h>

struct Set {
    unsigned int tag; // Assume tag is at most 32 bits
    unsigned char valid; // valid bit (0 or 1)
};

struct Cache {
    struct Set *sets;
    int numSets;
};

unsigned int getSet(unsigned int address) {
    return (address >> 1) & 0x7; // 2-byte blocks; 8 sets so 3 set bits
}

unsigned int getTag(unsigned int address) {
    return address >> 4; // total of 4 bits for offset and set
}

struct Cache* mallocCache(int numSets) {
    // malloc pointers for cache and array of sets
    struct Cache *cache = (struct Cache*) malloc(sizeof(struct Cache));
    cache->sets = (struct Set*) malloc(numSets * sizeof(struct Set));
    // set numSets value
    cache->numSets = numSets;

    // initialize validity of each set to 0
    for (int i=0; i<numSets; i++)
        cache->sets[i].valid = 0;

    return cache;
}

void freeCache(struct Cache *cache) {
    free(cache->sets);
    free(cache);
}

void printSet(struct Set *set, int setIndex) {
    printf("set: %x - tag: %x - valid: %u\n", setIndex, set->tag, set->valid);
}

void printCache(struct Cache *cache) {
    // loop through valid sets and print them
    for (int i=0; i<cache->numSets; i++)
        if (cache->sets[i].valid)
            printSet(&cache->sets[i], i);
}

void readValue(struct Cache *cache, unsigned int address) {
    // initialize variables from set
    int set_i = getSet(address);
    int set_tag = getTag(address);

    // test if set is valid and has right tag. Print appropriate output
    printf("Looking for set: %x - Tag: %x\n", set_i, set_tag);
    if (cache->sets[set_i].valid && cache->sets[set_i].tag == set_tag) {
        printf("Hit!\n");
    } else {
        if (cache->sets[set_i].valid) {
            printf("Conflict Miss!\n");
        } else {
            printf("Cold Miss!\n");
        }

        // update tag and set validity of set to True
        cache->sets[set_i].tag = set_tag;
        cache->sets[set_i].valid = 1;
    }
}

unsigned int readUnsignedIntFromHex() {
    char buffer[10];
    char *p = NULL;
    unsigned int n;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        n = strtoul(buffer, &p, 16);
        if (buffer != p) {
            break;
        }
        printf("Invalid input - try again: ");
    }
    return n;
}

int main() {  
    struct Cache *cache = mallocCache(8);

    char buffer[10];
    char c;
    do {
        printf("Enter 'r' for read, 'p' to print, 'q' to quit: ");
        fgets(buffer, sizeof(buffer), stdin);

        c = buffer[0];
        if (c == 'r') {                     
             printf("Enter 32-bit unsigned hex address: ");
             unsigned int a = readUnsignedIntFromHex();
             readValue(cache, a);
        } else if (c == 'p') {
             printCache(cache);
        }
    } while (c != 'q');

    freeCache(cache);
    return 0;
}