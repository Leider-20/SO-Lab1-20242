#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum line length
#define MAX_LINE_LENGTH 1024

void reverse_lines(FILE *input, FILE *output) {
    char **lines = NULL;
    size_t lines_size = 0;
    size_t lines_count = 0;
    char *line = NULL;
    size_t len = 0;

    // Read lines from input file
    while (getline(&line, &len, input) != -1) {
        char **temp = realloc(lines, (lines_count + 1) * sizeof(char *));
        if (temp == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        lines = temp;
        lines[lines_count] = strdup(line);
        if (lines[lines_count] == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        lines_count++;
    }

    free(line);

    // Write lines to output file in reverse order
    for (size_t i = lines_count; i > 0; i--) {
        fprintf(output, "%s", lines[i - 1]);
        free(lines[i - 1]);
    }
    free(lines);
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;

    // Handle command line arguments
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    } else if (argc == 3) {
        // Open input and output files
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
            return 1;
        }
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            fclose(input);
            return 1;
        }
    } else if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    }

    // Process lines and output
    reverse_lines(input, output);

    // Close files
    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);

    return 0;
}
