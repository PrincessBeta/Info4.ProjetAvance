#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"
/**
 * @file vote_Uninominal_Un_Tour.c
 * @brief Programme principal pour le vote uninominal à un tour
 * @author Yousra Arroui
 */

/**
 * @brief Affiche un tableau d'entiers dans la console de manière formatée.
 *
 * Affiche les étiquettes de ligne et de colonne, ainsi que les données du tableau.
 *
 * @param table Le tableau d'entiers.
 * @param numRows Le nombre de lignes dans le tableau.
 * @param numCols Le nombre de colonnes dans le tableau.
 * @param rowLabel L'étiquette de ligne.
 * @param colLabel L'étiquette de colonne.
 */
void printTable(int **table, int numRows, int numCols, const char *rowLabel, const char *colLabel) {
    // Imprime les étiquettes de colonne
    printf("\t%s\t", colLabel);
    for (int j = 0; j < numCols; j++) {
        printf("%d\t", j + 1);
    }
    printf("\n");

    // Imprime la ligne de séparation
    printf("\t");
    for (int j = 0; j <= numCols; j++) {
        printf("--------");
    }
    printf("\n");

    // Imprime les données de la table
    for (int i = 0; i < numRows; i++) {
        // Imprime l'étiquette de ligne
        printf("%s %d |\t", rowLabel, i + 1);

        // Imprime les données de la ligne
        for (int j = 0; j < numCols; j++) {
            printf("%d\t", table[i][j]);
        }

        printf("\n");
    }
}

/**
 * @brief Crée un tableau de votes à partir d'une matrice CSV.
 *
 * @param csvMatrix La matrice CSV contenant les données des votes.
 * @return Un tableau d'entiers représentant les votes.
 */
int** createVoteTable(Matrix *csvMatrix) {
    // Tableau de votes
    int** voteTable;

    // Vérifie si la matrice CSV est valide
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
    // Rempli le tableau de votes
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

/**
 * @brief Crée une matrice de scores à partir d'un tableau de votes.
 *
 * @param voteTable Le tableau de votes.
 * @param numRows Le nombre de lignes dans le tableau de votes.
 * @param numCols Le nombre de colonnes dans le tableau de votes.
 * @return Une matrice de scores représentant les résultats.
 */
int** createScoreMatrix(int** voteTable, int numRows, int numCols) {
    // Tableau de scores
    int** scoreMatrix;

    // Vérifie si le tableau de votes est valide
    scoreMatrix = (int**)malloc(numCols * sizeof(int*));
    if (scoreMatrix == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de scores\n");
        exit(1);
    }

    // Nombre de colonnes dans le tableau de scores
    int numBurgers = 10;

    for (int i = 0; i < numBurgers; i++) {
        // Alloucation dynamique de la ligne du tableau de scores
        scoreMatrix[i] = (int*)calloc(numCols, sizeof(int));
        if (scoreMatrix[i] == NULL) {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la ligne %d de la matrice de scores\n", i);
            exit(1);
        }

        // Parcours du tableau de votes et mise à jour du tableau de scores
        for (int j = 0; j < numRows; j++) {
            // Récupére le vote pour le burger i
            int vote = voteTable[j][i];
            // Si le vote est valide, on incrémente le score du burger correspondant
            if (vote != -1) {
                scoreMatrix[i][vote - 1]++;  // -1 car les votes commencent à 1, mais les indices à 0
            }
        }
    }

    return scoreMatrix;
}

/**
 * @brief Trouve le gagnant à partir d'une matrice de scores.
 *
 * @param scoreMatrix La matrice de scores.
 * @param numBurgers Le nombre de colonnes dans la matrice de scores.
 * @param numScores Le nombre de lignes dans la matrice de scores.
 * @return L'indice du gagnant.
 */
int findWinner(int **scoreMatrix, int numBurgers, int numScores) {
    int winner = 0;

    // Parcoure chaque colonne (note)
    for (int j = 0; j < numBurgers; j++) {
        // Parcoure chaque ligne (burger) à partir de la deuxième ligne
        for (int i = 1; i < numBurgers; i++) {
            // Compare les scores du burger actuel avec le gagnant actuel
            if (scoreMatrix[i][j] > scoreMatrix[winner][j]) {
                winner = i;  // Mettez à jour le gagnant
            } else if (scoreMatrix[i][j] == scoreMatrix[winner][j]) {
                // En cas d'égalité, passe à la prochaine colonne
                continue;
            } else {
                // Si le score est inférieur, passe à la prochaine colonne
                break;
            }
        }
    }

    // Ajoute une impression pour voir le résultat de la comparaison
    printf("Winner: %d\n", winner + 1);

    return winner;
}



/**
 * @brief Fonction principale.
 *
 * Charge un fichier CSV, crée un tableau de votes, une matrice de scores,
 * et trouve le gagnant du vote Condorcet.
 *
 * @return 0 si l'exécution s'est déroulée avec succès.
 */

int main() {
    const char *filename = "VoteJugement.csv"; // Nom du fichier CSV
    Matrix matrice;
    countRows(filename, &matrice);
    countCols(filename, &matrice);
    createMatrix(filename, &matrice);

    // Utilise la fonction createVoteTable pour obtenir le tableau de votes
    int **voteTable = createVoteTable(&matrice);

    // Affiche le tableau de votes
    printf("\nTableau de Votes :\n");
    int numCols = 10;
    printTable(voteTable, matrice.rows - 1, numCols, "Electeur", "Burger");

    // Crée la matrice de scores
    int **scoreMatrix = createScoreMatrix(voteTable, matrice.rows - 1, numCols);

    // Affiche la matrice de scores
    printf("\nMatrice de Scores :\n");
    printTable(scoreMatrix, numCols, numCols, "Burger", "Note");

    // Utilise la fonction findWinner pour obtenir le gagnant
    int winner = findWinner(scoreMatrix, numCols, numCols);

    // Affiche le gagnant
    printf("\nLe burger gagnant est : Burger %d\n", winner + 1);

    // Libére la mémoire des tableaux
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


