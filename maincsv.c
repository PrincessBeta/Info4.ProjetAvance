#include <stdio.h>
#include "lecture_csv.h"

int main() {
    const char *filename = "VoteCondorcet.csv";
    Matrix matrice;

    countRows(filename,&matrice);
    countCols(filename,&matrice);

    if (matrice.rows == -1 || matrice.cols == -1) {
        printf("Error while counting rows or columns.\n");
        return 1;
    }

    createMatrix(filename, &matrice);

    if (&matrice.data == NULL) {
        printf("Error while creating the matrix.\n");
        return 1;
    }

    printMatrix(&matrice);

    freeMatrix(&matrice);

    return 0; 
}