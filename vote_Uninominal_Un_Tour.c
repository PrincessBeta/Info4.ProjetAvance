#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"

int** createVoteTable(Matrix *csvMatrix) {
    // Tableau de votes
    int** voteTable;

    // Vérifiez si la matrice CSV est valide
    if (csvMatrix == NULL || csvMatrix->data == NULL) {
        fprintf(stderr, "Erreur : Matrice CSV invalide\n");
        exit(1);
    }

    // Allouez dynamiquement le tableau de votes
    voteTable = (int**)malloc(csvMatrix->rows * sizeof(int*));
    if (voteTable == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de votes\n");
        exit(1);
    }

    // Nombre de colonnes dans le tableau de votes
    int numCols = 10;
    // Remplisser le tableau de votes
    for (int i = 1; i < csvMatrix->rows; i++) {
        // Allouez dynamiquement la ligne du tableau de votes
        voteTable[i -1] = (int*)malloc(numCols * sizeof(int));
        if (voteTable[i - 1] == NULL) {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la ligne %d de la matrice de votes\n", i);
            exit(1);
        }

        for (int j = 4; j < csvMatrix->cols; j++) {
            // Convertissez la chaîne de caractères en entier
            voteTable[i - 1][j - 4] = atoi(csvMatrix->data[i][j]);
        }
    }
    return voteTable;
}


int main() {
    const char *filename = "VoteCondorcet.csv"; // Nom du fichier CSV
    Matrix matrice;
    countRows(filename, &matrice);
    countCols(filename, &matrice);
    createMatrix(filename, &matrice);

    // Créez le tableau de votes
    int **voteTable = createVoteTable(&matrice);

    // Affichez le tableau de votes
    int numCols = 10;
    for (int i = 0; i < matrice.rows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d\t", voteTable[i][j]);
        }
        printf("\n");
    }

    // Libérez la mémoire du tableau de votes
    for (int i = 0; i < matrice.rows; i++) {
        free(voteTable[i]);
    }
    free(voteTable);
    return 0;
}

