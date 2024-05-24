#include <stdio.h>
#include "matrix_operations.h"
#include "matrix_io.h"
#include "main.h"

int is_scalar_matrix(int rows, int cols) {
    return (rows == 1 && cols == 1);
}

int main() {
    int matrix1rows = 0;
    int matrix1cols = 0;
    int matrix2rows = 0;
    int matrix2cols = 0;
    printf("Enter the first matrix:\n");
    float** matrix1 = read_matrix(&matrix1rows, &matrix1cols);
    if (matrix1 == NULL) {
        printf("Error reading the first matrix.\n");
        return 1;
    }

    char operation;
    if (is_scalar_matrix(matrix1rows, matrix1cols)) {
        operation = '*';
    } else {
        printf("Enter the operation (+, - or *):\n");
        if (scanf(" %c", &operation) != 1 || (operation != '+' && operation != '-' && operation != '*')) {
            printf("Invalid operation.\n");
            return 1;
        }
        while (getchar() != '\n');
    }

    printf("Enter the second matrix:\n");
    float** matrix2 = read_matrix(&matrix2rows, &matrix2cols);
    if (matrix2 == NULL) {
        printf("Error reading the second matrix.\n");
        return 1;
    }

    float** result;

    switch (operation) {
    case '+':
        result = add(matrix1, matrix1rows, matrix1cols, matrix2, matrix2rows, matrix2cols);
        break;
    case '-':
        result = subtract(matrix1, matrix1rows, matrix1cols, matrix2, matrix2rows, matrix2cols);
        break;
    case '*':
        result = multiply(matrix1, matrix1rows, matrix1cols, matrix2, matrix2rows, matrix2cols);
        break;
    }

    if (result == NULL) {
        printf("Error performing the operation.\n");
    } else {
        if (is_scalar_matrix(matrix1rows, matrix1cols) || is_scalar_matrix(matrix2rows, matrix2cols)) {
            printf("The result is:\n");
            print_matrix_with_operator(
                matrix1, matrix1rows, matrix1cols,
                operation, matrix2, matrix2rows,
                matrix2cols, result, matrix1rows > matrix2rows ? matrix1rows : matrix2rows,
                matrix1cols > matrix2cols ? matrix1cols : matrix2cols);
        } else {
            printf("The result is:\n");
            print_matrix_with_operator(
                matrix1, matrix1rows, matrix1cols,
                operation, matrix2, matrix2rows,
                matrix2cols, result, matrix1rows, matrix1cols
            );
        }
    }
    return 0;
}
