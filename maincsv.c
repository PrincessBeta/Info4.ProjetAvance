#include <stdio.h>
#include "lecture_csv.h"

int main() {
    const char *filename = "VoteCondorcet.csv"; // Replace with your CSV file path

    // Use the countRows and countCols functions to determine the dimensions of the CSV data.
    int nbrows = countRows(filename);
    int nbcolumns = countCols(filename);

    if (nbrows == -1 || nbcolumns == -1) {
        printf("Error while counting rows or columns.\n");
        return 1; // Return an error code
    }

    // Use the createMatrix function to read the CSV data into a matrix.
    Matrix *matrix = createMatrix(filename, nbrows, nbcolumns);

    if (matrix == NULL) {
        printf("Error while creating the matrix.\n");
        return 1; // Return an error code
    }

    // Use the printMatrix function to display the CSV data.
    printMatrix(matrix, nbrows, nbcolumns);

    // Free the allocated memory.
    freeMatrix(matrix, nbrows, nbcolumns);

    return 0; // Return 0 to indicate success
}