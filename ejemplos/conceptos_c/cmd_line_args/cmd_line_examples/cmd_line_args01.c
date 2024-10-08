/*
Author: Adalbert Gerald Soosai Raj
URL: https://pages.cs.wisc.edu/~gerald/cs354/Spring2019/code/lecture03/cmd_line_args01.c
*/

#include <stdio.h>
#include <stdlib.h>

// Argument vector (argv) is declared as an array of pointers to characters.
int main(int argc, char *argv[])
{
    int i;

    if (argc != 4) {
        fprintf(stderr, "USAGE: %s <name> <age> <alpha>\n", argv[0]);
        exit(1);
    }
    
    for (i = 0; i < 4; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
