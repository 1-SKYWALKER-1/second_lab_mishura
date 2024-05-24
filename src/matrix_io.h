#ifndef MATRIX_IO_H
#define MATRIX_IO_H

void print_matrix_with_operator(float **matrix1, int rows1, int cols1, char op, float **matrix2, int rows2, int cols2, float **result, int resultrows, int resultcols);
float **read_matrix(int *r, int *c);

#endif // MATRIX_IO_H
