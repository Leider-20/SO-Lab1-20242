/*
Author: Adalbert Gerald Soosai Raj
URL: https://pages.cs.wisc.edu/~gerald/cs354/Spring2019/code/lecture04/dynamic_array_inclass.c
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s <num_elems>\n", argv[0]);
        exit(1);
    }

    int num = atoi(argv[1]);
    printf("num = %d\n", num);

    // create a dynamic array on the heap 
    int *a = malloc(num * sizeof(int));

    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < num; ++i) {
        a[i] = i;
    }

    for (int i = 0; i < num; ++i) {
        printf("a[%d] = %d\n", i, a[i]);
    }

    a = realloc(a, 2 * num * sizeof(int));

    for (int i = 0; i < 2 * num; ++i) {
        printf("a[%d] = %d\n", i, a[i]);
    }

    free(a);

    free(a);

    return 0;
}
