#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct{
  double** data;
  int rows;
  int cols;
} matrix; 

int mm_alloc(matrix* mat);
int mm_free (matrix* mat);
int mm_print(matrix* mat);
int mm_read (char* filename, matrix* mat);
matrix* mm_matrix_mult(matrix* mat1, matrix* mat2);

#endif 