#include <stdio.h>
#include "lecture_csv.h"

int main() {
    const char *filename = "VoteCondorcet.csv"; // Replace with your CSV file path
    Matrix matrice;
    // Use the countRows and countCols functions to determine the dimensions of the CSV data.
    countRows(filename,&matrice);
    countCols(filename,&matrice);

    if (matrice.rows == -1 || matrice.cols == -1) {
        printf("Error while counting rows or columns.\n");
        return 1; // Return an error code
    }

    // Use the createMatrix function to read the CSV data into a matrix.
    createMatrix(filename, &matrice);

    if (&matrice.data == NULL) {
        printf("Error while creating the matrix.\n");
        return 1; // Return an error code
    }

    // Use the printMatrix function to display the CSV data.
    printMatrix(&matrice);

    // Free the allocated memory.
    freeMatrix(&matrice);

    return 0; // Return 0 to indicate success
}