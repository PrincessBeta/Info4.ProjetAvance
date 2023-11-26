#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"
/**
 * @file vote_Uninominal_Deux_Tour.c
 * @brief Programme principal pour le vote uninominal à deux tours
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

int *createTableauScoreT1(int **voteTable, int numCols, int numRows)
{
    int *scoreMatrix;
    scoreMatrix = (int *)malloc(numCols * sizeof(int));
    if (scoreMatrix == NULL)
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de scores\n");
        exit(1);
    }
    for(int j = 0; j < numRows; j++){
        int min = voteTable[0][0];
        for(int i = 1; i < numCols; i++){
            if (voteTable[j][i] < min && voteTable[j][i] != -1){
                min = voteTable[j][i];
            }
        }
        for(int i = 0; i < numCols; i++){
            if (voteTable[j][i] == min){
                scoreMatrix[i]++;
            }
        }
    }
    return scoreMatrix;
}

int *createTableauScoreT2(int **voteTable, int numCols, int numRows, int *tab_gagnant)
{
    int *scoreMatrix;
    scoreMatrix = (int *)malloc(numCols * sizeof(int));
    if (scoreMatrix == NULL)
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de scores\n");
        exit(1);
    }
    for(int j = 0; j < numRows; j++){
        if(voteTable[j][tab_gagnant[0]-1] < voteTable[j][tab_gagnant[1]-1]){
            scoreMatrix[tab_gagnant[1]-1]++;
        }
        else if (voteTable[j][tab_gagnant[0]-1] > voteTable[j][tab_gagnant[1]-1]){
            scoreMatrix[tab_gagnant[0]-1]++;
        }
    }
    return scoreMatrix;
}

void printTableauScore(int *tableauScore, int numCols)
{
    printf("\nTableau de Scores :\n");
    printf("\tBurger\tScore\n");
    printf("\t------- --------\n");
    for (int i = 0; i < numCols; i++)
    {
        printf("\t%d\t%d\n", i + 1, tableauScore[i]);
    }
}

void findWinnersUni1(int *tableauScore, int numBurgers, int *tab_gagnant)
{
    int max = tableauScore[0];
    int indice = 0;
    for (int i = 1; i < numBurgers; i++)
    {
        if (tableauScore[i] > max)
        {
            max = tableauScore[i];
        }
    }
    for (int i = 0; i < numBurgers; i++){
        if (tableauScore[i] == max){
            tab_gagnant[indice] = i+1;
            indice++;
        }
    }
}
void findWinnersUni2Tour1(int *tableauScore, int numBurgers, int *tab_gagnant)
{
    int indice = 0;
    while(indice < 2){
        int max1 = tableauScore[0];
        int max2 = tableauScore[1];
        if (max1 < max2){
            int temp = max1;
            max1 = max2;
            max2 = temp;
        }
        for (int i = 2; i < numBurgers; i++)
        {
            if (tableauScore[i] <= max1 && tableauScore[i] > max2)
            {
                max2 = tableauScore[i];
            }
            if (tableauScore[i] > max1)
            {
                max2 = max1;
                max1 = tableauScore[i];
            } 
        }
        for (int i = 0; i < numBurgers; i++){
            if (tableauScore[i] == max1 || tableauScore[i] == max2){
                tab_gagnant[indice] = i+1;
                indice++;
                if (indice == 2){
                    break;
                }
            }
        }
    }
}
int findWinnersUni2Tour2(int *tableauScore, int *tab_gagnant)
{
    int i_gagnant;
    if(tableauScore[tab_gagnant[0]-1] > tableauScore[tab_gagnant[1]-1]){
        i_gagnant = tab_gagnant[0];
    }
    else if (tableauScore[tab_gagnant[0]-1] < tableauScore[tab_gagnant[1]-1]){
        i_gagnant = tab_gagnant[1];
    }
    else{
        i_gagnant = 0;
    }
    return i_gagnant;
}

int main(int argc, char **argv)
{
    if(argc != 3){
        fprintf(stderr, "Erreur : Nombre d'arguments invalide\n");
        exit(1);
    }
    char *method = argv[2];
    if(strcmp(method, "uni1") != 0 && strcmp(method, "uni2") != 0){
        fprintf(stderr, "Erreur : Méthode de vote invalide\n");
        exit(1);
    }
    int i_method;
    if(strcmp(method, "uni1") == 0){
        i_method = 1;
    }
    if(strcmp(method, "uni2") == 0){
        i_method = 2;
    }
    const char *filename = argv[1]; // peut être changé par voteCondorcet.csv
    Matrix matrice;
    countRows(filename, &matrice);
    countCols(filename, &matrice);
    createMatrix(filename, &matrice);

    int **voteTable = createVoteTable(&matrice);

    printf("\nTableau de Votes :\n");
    int numCols = 10;
    int numRows = matrice.rows - 1;
    printTable(voteTable, numRows, numCols, "Electeur", "Burger");

    int* tab_score;
    int tab_gagnant[numCols];
    for (int i = 0; i < numCols; i++)
    {
        tab_gagnant[i] = 0;
    }

    switch(i_method){
        case 1:
            printf("\nMéthode de vote : Uninominal à un tour\n");
            tab_score = createTableauScoreT1(voteTable, numCols, numRows);
            printTableauScore(tab_score, numCols);
            findWinnersUni1(tab_score, numCols, tab_gagnant);
            printf("\nLe(s) burger(s) gagnant(s) :\n");
            for(int i = 0; i < numCols; i++){
                if(tab_gagnant[i] != 0){
                    printf("\nBurger %d\n", tab_gagnant[i]);
                }
            }
            break;
        case 2:
            printf("\nMéthode de vote : Uninominal à deux tours\n");
            tab_score = createTableauScoreT1(voteTable, numCols, numRows);
            printf("\nPremier tour :\n");
            printTableauScore(tab_score, numCols);
            findWinnersUni2Tour1(tab_score, numCols, tab_gagnant);
            printf("\nLe(s) burger(s) gagnant(s) du premier tour sont Burger %d et Burger %d\n", tab_gagnant[0], tab_gagnant[1]);
            tab_score = createTableauScoreT2(voteTable, numCols, numRows, tab_gagnant);
            printf("\nDeuxieme tour :\n");
            printTableauScore(tab_score, numCols);
            int winner = findWinnersUni2Tour2(tab_score, tab_gagnant);
            printf("\nLe burger gagnant du deuxieme tour est Burger %d\n", winner);
            break;    
    }

    for (int i = 0; i < matrice.rows - 1; i++)
    {
        free(voteTable[i]);
    }
    free(voteTable);

    free(tab_score);

    return 0;
}
