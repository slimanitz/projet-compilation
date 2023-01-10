#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

// Function that creates a two dimensional matrix
char **create_matrix(int m, int n)
{
    char **matrix;

    matrix = malloc(sizeof(char *) * m);

    for (int i = 0; i < m; i++)
        matrix[i] = malloc(sizeof(char) * n);

    return matrix;
}