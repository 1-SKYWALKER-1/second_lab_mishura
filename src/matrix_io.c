#include "matrix_io.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_operations.h"

void print_matrix_with_operator(float **matrix1, int rows1, int cols1, char op, float **matrix2, int rows2, int cols2, float **result, int resultrows, int resultcols) {
    int max_rows = rows1 > rows2 ? rows1 : rows2;
    max_rows = max_rows > resultrows ? max_rows : resultrows;

    for (int i = 0; i < max_rows; i++) {
        printf("| ");

        if (i < rows1) {
            if (cols1 == 1) {
                printf("%.1f ", matrix1[i][0]);  // Scalar matrix
            } else {
                for (int j = 0; j < cols1; j++) {
                    printf("%.1f ", matrix1[i][j]);
                }
            }
        } else {
            printf("    ");
        }

        printf("|");

        if (i == max_rows / 2) {
            printf(" %c ", op);
        } else {
            printf("   ");
        }

        printf("| ");

        if (i < rows2) {
            if (cols2 == 1) {
                printf("%.1f ", matrix2[i][0]);  // Scalar matrix
            } else {
                for (int j = 0; j < cols2; j++) {
                    printf("%.1f ", matrix2[i][j]);
                }
            }
        } else {
            printf("    ");
        }

        printf("|");

        if (i == max_rows / 2) {
            printf(" = ");
        } else {
            printf("   ");
        }

        if (i < resultrows) {
            printf("| ");
            if (resultcols == 1) {
                printf("%.1f ", result[i][0]);  // Scalar result
            } else {
                for (int j = 0; j < resultcols; j++) {
                    printf("%.1f ", result[i][j]);
                }
            }
            printf("|\n");
        } else {
            printf("\n");
        }
    }
}

float **read_matrix(int *r, int *c) {
    char input[1000];
    int hasOpeningBracket = 0;
    int hasClosingBracket = 0;
    int rows = 0;
    int cols = 0;

    printf("Enter the matrix in the format [2 2; 2 2]:\n");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return NULL;
    }

    char *newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if (!isdigit(input[i]) && input[i] != '.' && input[i] != ' ' && input[i] != ';' && input[i] != '[' && input[i] != ']' && input[i] != '-') {
            printf("Invalid character in input: '%c'. Only numbers, '.', '[', ']', ';', '-', and spaces are allowed.\n", input[i]);
            return NULL;
        }
        if (input[i] == '[') {
            hasOpeningBracket = 1;
        } else if (input[i] == ']') {
            hasClosingBracket = 1;
        }
    }

    if (hasOpeningBracket != hasClosingBracket) {
        printf("Error: Mismatched brackets in input.\n");
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        if (input[i] == ' ') {
            if (i > 0 && input[i - 1] != ' ') {
                cols++;
            }
        } else if (input[i] == ';') {
            rows++;
        }
    }

    cols++;
    rows++;
    cols /= rows;

    float** matrix = createMatrix(rows, cols);

    if (matrix == NULL) {
        printf("Failed to allocate memory for the matrix.\n");
        return NULL;
    }

    char *token = strtok(input, "[ ;]");
    int row = 0, col = 0;
    while (token != NULL) {
        matrix[row][col++] = atof(token);
        if (col == cols) {
            row++;
            col = 0;
        }
        token = strtok(NULL, "[ ;]");
    }
    *r = rows;
    *c = cols;
    return matrix;
}
