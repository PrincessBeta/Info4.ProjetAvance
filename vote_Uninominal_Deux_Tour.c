#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"
/**
 * @file vote_Uninominal_Un_Tour.c
 * @brief Programme principal pour le vote uninominal à un tour
 * @author Yousra Arroui
 */

void printTable(int **table, int numRows, int numCols, const char *rowLabel, const char *colLabel)
{
    printf("\t%s\t", colLabel);
    for (int j = 0; j < numCols; j++)
    {
        printf("%d\t", j + 1);
    }
    printf("\n");

    printf("\t");
    for (int j = 0; j <= numCols; j++)
    {
        printf("--------");
    }
    printf("\n");

    for (int i = 0; i < numRows; i++)
    {
        printf("%s %d |\t", rowLabel, i + 1);

        for (int j = 0; j < numCols; j++)
        {
            printf("%d\t", table[i][j]);
        }

        printf("\n");
    }
}

int **createVoteTable(Matrix *csvMatrix)
{
    int **voteTable;

    if (csvMatrix == NULL || csvMatrix->data == NULL)
    {
        fprintf(stderr, "Erreur : Matrice CSV invalide\n");
        exit(1);
    }

    voteTable = (int **)malloc(csvMatrix->rows * sizeof(int *));
    if (voteTable == NULL)
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de votes\n");
        exit(1);
    }

    int numCols = 10;
    for (int i = 1; i < csvMatrix->rows; i++)
    {
        voteTable[i - 1] = (int *)malloc(numCols * sizeof(int));
        if (voteTable[i - 1] == NULL)
        {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la ligne %d de la matrice de votes\n", i);
            exit(1);
        }

        for (int j = 4; j < csvMatrix->cols; j++)
        {
            voteTable[i - 1][j - 4] = atoi(csvMatrix->data[i][j]);
        }
    }
    return voteTable;
}

int *createTableauScore(int **voteTable, int numCols, int numRows)
{
    int *scoreMatrix;
    scoreMatrix = (int *)malloc(numCols * sizeof(int));
    if (scoreMatrix == NULL)
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de scores\n");
        exit(1);
    }
    for (int i = 0; i < numCols; i++)
    {
        scoreMatrix[i] = 0;
    }
    for (int i = 0; i < numCols; i++)
    {   
        for (int j = 0; j < numRows; j++)
        {
            if (voteTable[j][i] != -1){
                scoreMatrix[i] += voteTable[j][i];
            }
            
        }
    }
    return scoreMatrix;
}

void printTableauScore(int *tableauScore, int numCols)
{
    printf("\nTableau de Scores :\n");
    printf("\tBurger\tScore\n");
    printf("\t--------\t--------\n");
    for (int i = 0; i < numCols; i++)
    {
        printf("\t%d\t%d\n", i + 1, tableauScore[i]);
    }
}

int findWinTour2(int *tableauScore, int numBurgers, int numScores, int winners[2])
{
    return winners[0] + 1;
}

int findWinner(int *tableauScore, int numBurgers, int numScores)
{
    int min1 = tableauScore[0];
    int min2 = tableauScore[1];
    int indice1 = 0;
    int indice2 = 1;
    for (int i = 1; i < numBurgers; i++)
    {
        if (tableauScore[i] < min1)
        {
            min2 = min1;
            indice2 = indice1;
            min1 = tableauScore[i];
            indice1 = i;
        }
        else if (tableauScore[i] < min2)
        {
            min2 = tableauScore[i];
            indice2 = i;
        }
    }

    int winners[2] = {indice1, indice2};

    return findWinTour2(tableauScore, numBurgers, numScores, winners);
}

int main()
{
    const char *filename = "voteJugement.csv"; 
    Matrix matrice;
    countRows(filename, &matrice);
    countCols(filename, &matrice);
    createMatrix(filename, &matrice);

    int **voteTable = createVoteTable(&matrice);

    printf("\nTableau de Votes :\n");
    int numCols = 10;
    int numRows = matrice.rows - 1;
    printTable(voteTable, numRows, numCols, "Electeur", "Burger");

    int *tab_score = createTableauScore(voteTable, numCols, numRows);

    printTableauScore(tab_score, numCols);

    int winner = findWinner(tab_score, numCols, 10);

    printf("\nLe burger gagnant est : Burger %d\n", winner);

    for (int i = 0; i < matrice.rows - 1; i++)
    {
        free(voteTable[i]);
    }
    free(voteTable);

    free(tab_score);

    return 0;
}