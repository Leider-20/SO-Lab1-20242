#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void reverse_lines(FILE *input, FILE *output) {
    char **lines = NULL; // Arreglo de líneas
    size_t size = 0, capacity = 10; // Tamaño del arreglo y capacidad inicial
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Se Inicializa la memoria para almacenar las líneas
    lines = malloc(capacity * sizeof(char *));
    if (!lines) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    // Leemos las líneas del archivo
    while ((read = getline(&line, &len, input)) != -1) {
        if (size >= capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char *));
            if (!lines) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
        }
        lines[size] = strdup(line); // Copiamos la línea leída al arreglo
        if (!lines[size]) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        size++;
    }
    free(line);

    // Imprimir las líneas en orden inverso
    for (ssize_t i = size - 1; i >= 0; i--) {
        fprintf(output, "%s", lines[i]);
        free(lines[i]); // Liberar memoria de cada línea
    }

    free(lines); // Liberar memoria del arreglo de líneas
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;

    // Demasiados argumentos
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Un archivo de entrada especificado
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    // Un archivo de salida especificado
    if (argc == 3) {
        // Verificamos si el archivo de entrada es el mismo que el de salida
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
            exit(1);
        }

        output = fopen(argv[2], "w");
        if (!output) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }

    // Ejecutamos la función para invertir las líneas
    reverse_lines(input, output);

    // Cerramos los archivos si no son stdin o stdout
    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);

    return 0;
}
