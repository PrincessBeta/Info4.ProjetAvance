#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"

void printTable(int **table, int numRows, int numCols, const char *rowLabel, const char *colLabel) {
    // Imprimer les étiquettes de colonne
    printf("\t%s\t", colLabel);
    for (int j = 0; j < numCols; j++) {
        printf("%d\t", j + 1);
    }
    printf("\n");

    // Imprimer la ligne de séparation
    printf("\t");
    for (int j = 0; j <= numCols; j++) {
        printf("--------");
    }
    printf("\n");

    // Imprimer les données de la table
    for (int i = 0; i < numRows; i++) {
        // Imprimer l'étiquette de ligne
        printf("%s %d |\t", rowLabel, i + 1);

        // Imprimer les données de la ligne
        for (int j = 0; j < numCols; j++) {
            printf("%d\t", table[i][j]);
        }

        printf("\n");
    }
}


int** createVoteTable(Matrix *csvMatrix) {
    // Tableau de votes
    int** voteTable;

    // Vérifiez si la matrice CSV est valide
    if (csvMatrix == NULL || csvMatrix->data == NULL) {
        fprintf(stderr, "Erreur : Matrice CSV invalide\n");
        exit(1);
    }

    // Allocation dynamique du tableau de votes
    voteTable = (int**)malloc(csvMatrix->rows * sizeof(int*));
    if (voteTable == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de votes\n");
        exit(1);
    }

    // Nombre de colonnes dans le tableau de votes
    int numCols = 10;
    // Remplisser le tableau de votes
    for (int i = 1; i < csvMatrix->rows; i++) {
        // Allocation dynamique de la ligne du tableau de votes
        voteTable[i -1] = (int*)malloc(numCols * sizeof(int));
        if (voteTable[i - 1] == NULL) {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la ligne %d de la matrice de votes\n", i);
            exit(1);
        }

        for (int j = 4; j < csvMatrix->cols; j++) {
            // Convertir le vote en entier
            voteTable[i - 1][j - 4] = atoi(csvMatrix->data[i][j]);
        }
    }
    return voteTable;
}

int** createScoreMatrix(int** voteTable, int numRows, int numCols) {
    // Tableau de scores
    int** scoreMatrix;

    // Vérifiez si le tableau de votes est valide
    scoreMatrix = (int**)malloc(numCols * sizeof(int*));
    if (scoreMatrix == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de scores\n");
        exit(1);
    }

    // Nombre de colonnes dans le tableau de scores
    int numBurgers = 10;

    for (int i = 0; i < numBurgers; i++) {
        // Allouocation dynamique de la ligne du tableau de scores
        scoreMatrix[i] = (int*)calloc(numCols, sizeof(int));
        if (scoreMatrix[i] == NULL) {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la ligne %d de la matrice de scores\n", i);
            exit(1);
        }

        // Parcours du tableau de votes et mise à jour du tableau de scores
        for (int j = 0; j < numRows; j++) {
            // Récupérer le vote pour le burger i
            int vote = voteTable[j][i];
            // Si le vote est valide, on incrémente le score du burger correspondant
            if (vote != -1) {
                scoreMatrix[i][vote - 1]++;  // -1 car les votes commencent à 1, mais les indices à 0
            }
        }
    }

    return scoreMatrix;
}

int findWinner(int **scoreMatrix, int numBurgers, int numScores) {
    int winner = 0;

    // Parcourez chaque colonne (note)
    for (int j = 0; j < numBurgers; j++) {
        // Parcourez chaque ligne (burger) à partir de la deuxième ligne
        for (int i = 1; i < numBurgers; i++) {
            // Comparez les scores du burger actuel avec le gagnant actuel
            if (scoreMatrix[i][j] > scoreMatrix[winner][j]) {
                winner = i;  // Mettez à jour le gagnant
            } else if (scoreMatrix[i][j] == scoreMatrix[winner][j]) {
                // En cas d'égalité, passez à la prochaine colonne
                continue;
            } else {
                // Si le score est inférieur, passez à la prochaine colonne
                break;
            }
        }
    }

    // Ajoutez une impression pour voir le résultat de la comparaison
    printf("Winner: %d\n", winner + 1);

    return winner;
}




int main() {
    const char *filename = "VoteJugement.csv";  // Remplacez par votre fichier CSV
    Matrix matrice;
    countRows(filename, &matrice);
    countCols(filename, &matrice);
    createMatrix(filename, &matrice);

    // Utilisez la fonction createVoteTable pour obtenir le tableau de votes
    int **voteTable = createVoteTable(&matrice);

    // Affichez le tableau de votes
    printf("\nTableau de Votes :\n");
    int numCols = 10;
    printTable(voteTable, matrice.rows - 1, numCols, "Electeur", "Burger");

    // Créez la matrice de scores
    int **scoreMatrix = createScoreMatrix(voteTable, matrice.rows - 1, numCols);

    // Affichez la matrice de scores
    printf("\nMatrice de Scores :\n");
    printTable(scoreMatrix, numCols, numCols, "Burger", "Note");

    // Utilisez la fonction findWinner pour obtenir le gagnant
    int winner = findWinner(scoreMatrix, numCols, numCols);

    // Affichez le gagnant
    printf("\nLe burger gagnant est : Burger %d\n", winner + 1);

    // Libérez la mémoire des tableaux
    for (int i = 0; i < matrice.rows - 1; i++) {
        free(voteTable[i]);
    }
    free(voteTable);

    for (int i = 0; i < numCols; i++) {
        free(scoreMatrix[i]);
    }
    free(scoreMatrix);

    return 0;
}


