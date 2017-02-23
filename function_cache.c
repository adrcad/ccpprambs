#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef MAX
#define MAX 20
#endif


int check_cache(int*, int);
void init_cache(int*);
int heavy_func(int);


int main(int argc, char *argv) {
    int input;

    while (1) {
        printf("Enter a number (or CTRL+C to finish):");
        scanf("%d", &input);
        printf("You have entered %d\n", heavy_func(input));
    }
    return 0;
}


int heavy_func(int a) {
    static int* cache;
    int i = -1, retval, j = 0;

    if (cache == NULL) {
        cache = malloc(MAX * sizeof(int));
        init_cache(cache);
    }

    i = check_cache(cache, a);
    if (i == -1) {
        printf("[INFO] Value not present in the cache. Computing it ...\n");
        retval = a;
        while (*(cache + j) != -1) {
            j++;
            if (j == MAX) {
                j = 0;
                break;
            }
        }
        *(cache + j) = retval;
    } else {
        printf("[INFO] Value already computed, retrieving it from cache ....\n");
        j = i;
    }

    return  *(cache + j);
}


int check_cache(int *cache, int value) {
    int index = -1, i = 0;

    if (cache == NULL)
        return index;

    printf("[INFO] Checking cache...\n[INFO] Value of the cache\n[INFO] ");
    for (int j = 0; j < MAX; ++j)
        printf("%d ", cache[j]);
    printf("\n");

    for (int i = 0; i < MAX; ++i) {
        if (cache[i] == value) {
            return i;
        }
    }
    return index;
}


void init_cache(int *cache) {
    printf("[INFO] Initializing the cache ...\n");
    for (int i = 0; i < MAX; ++i)
        *(cache + i) = -1;
    printf("[INFO] Initialization done !\n");
}