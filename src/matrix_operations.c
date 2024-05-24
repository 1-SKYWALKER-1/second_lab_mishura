#include "matrix_operations.h"
#include "stdio.h"
#include <malloc.h>

float **scalar_operation(float **matrix, float scalar, int rows, int cols, char operation) {
    float **result = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        result[i] = (float *)malloc(cols * sizeof(float));
    }
    if (result == NULL) {
        printf("Failed to allocate memory for the result matrix.\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (operation == '+') {
                result[i][j] = matrix[i][j] + scalar;
            } else if (operation == '-') {
                result[i][j] = matrix[i][j] - scalar;
            } else if (operation == '*') {
                result[i][j] = matrix[i][j] * scalar;
            } else {
                printf("Invalid operation.\n");
                return NULL;
            }
        }
    }
    return result;
}
float **createMatrix(int rows, int cols) {
    float **matrix = (float **)malloc(rows * sizeof(float*));
    if (matrix == NULL) return NULL;
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *)malloc(cols * sizeof(float));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
float **handle_scalar_matrices(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2, char operation) {
    if (is_scalar_matrix(rows1, cols1)) return scalar_operation(matrix2, matrix1[0][0], rows2, cols2, operation);


    if (is_scalar_matrix(rows2, cols2)) return scalar_operation(matrix1, matrix2[0][0], rows1, cols1, operation);
 
    return NULL;
}
float **add(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2) {
    float **scalar_result = handle_scalar_matrices(matrix1, rows1, cols1, matrix2, rows2, cols2, '+');
    if (scalar_result != NULL) return scalar_result;
 
    if (rows1 != rows2 || cols1 != cols2) {
        return NULL;
    }

    float **res = createMatrix(rows1, cols1);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            res[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return res;
}

float **subtract(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2) {
    float **scalar_result = handle_scalar_matrices(matrix1, rows1, cols1, matrix2, rows2, cols2, '-');
    if (scalar_result != NULL) return scalar_result;
   
    if (rows1 != rows2 || cols1 != cols2) return NULL;
   
    float **res = createMatrix(rows1, cols1);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            res[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return res;
}

float **multiply(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2) {
    float **scalar_result = handle_scalar_matrices(matrix1, rows1, cols1, matrix2, rows2, cols2, '*');
    if (scalar_result != NULL) return scalar_result;

    if (cols1 != rows2) return NULL;
    

    float **res = createMatrix(rows1, cols2);
    for (int i = 0; i < rows1; i++) {
    	for (int j = 0; j < cols2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
            	res[i][j] += matrix1[i][k] * matrix2[k][j];
		}
	}
    }
    return res;
}
