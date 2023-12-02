#include <stdio.h>
#include <stdlib.h>
#include "lecture_csv.h"



Matrix * trim_matrix_moodle(Matrix * m) {
    Matrix * new_mat = malloc(sizeof(Matrix));
    new_mat->data = malloc(m->rows * sizeof(char **));
    for (int i=0;i<m->rows-1;i++)
        new_mat->data[i] = malloc(sizeof(char*)*(m->cols-4));
    new_mat->rows = m->rows-1;
    new_mat->cols = m->cols-4;
    for (int i = 0;i<m->rows-1;i++) {
        for (int j = 0;j<m->cols-4;j++) {
            new_mat->data[i][j] = (m->data)[i+1][j+4];
        }
    }
    return new_mat;
}