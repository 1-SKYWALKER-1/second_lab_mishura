#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

float **scalar_operation(float **matrix, float scalar, int rows, int cols, char operation);
float **handle_scalar_matrices(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2, char operation);
float **add(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2);
float **subtract(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2);
float **multiply(float **matrix1, int rows1, int cols1, float **matrix2, int rows2, int cols2);
int is_scalar_matrix(int rows, int cols);
float **createMatrix(int rows, int cols);

#endif // MATRIX_OPERATIONS_H
