//
// matrix.h
// Facial gender detection
//
//
// EE 113D - Fall 2013
//  * Allen Wu
//  * Bryant Khau
//

#ifndef EE113D_MATRIX
#define EE113D_MATRIX

#include <stdlib.h>
#include "ee113d.h"

#define PRINT_MATRIX_DECIMALS 2

// Matrix data type
typedef struct {
    size_t rows, cols;
    double** data;
} Matrix;

// Pair
typedef struct {
    double value;
    int index;
} Pair;

// Helper functions
Matrix array2Matrix(double* array, size_t arrayLen, size_t rows, size_t cols);
void   printMatrix(Matrix m);
void   freeMatrix(Matrix* m);
Matrix newMatrix(size_t rows, size_t cols, bool clearMemory);

// Matrix/vector functions
double vectorNorm(Matrix a);
Pair   maxWithIndex(Matrix a);
double sum(Matrix a);
Matrix dotProduct(Matrix a, Matrix b);
Matrix transpose(Matrix input);
Matrix subtract(Matrix x, Matrix y);
Matrix column(Matrix m, int n);

Matrix matrixEach(Matrix n, double (*function)(), double (*extra)());


#endif
// EE113D_MATRIX