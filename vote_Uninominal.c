#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"
/**
 * @file vote_Uninominal.c
 * @brief Programme principal pour le vote uninominal à deux tours
 * @author Yousra Arroui
 */

int *createTableauScoreT1(int **voteTable, int numCols, int numRows)
{
    int *scoreMatrix = malloc(numCols * sizeof(int));

    for (int i = 0; i < numCols; i++)
    {
        scoreMatrix[i] = 0;
    }
    

    if (scoreMatrix == NULL)
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de scores\n");
        exit(1);
    }
    for(int j = 0; j < numRows; j++){
        int min = voteTable[j][0];
        for(int i = 1; i < numCols; i++){
            if (voteTable[j][i] < min && voteTable[j][i] != -1){
                min = voteTable[j][i];
            }
        }
        int nbVotes = 0;
        for(int i = 0; i < numCols; i++){
            if (voteTable[j][i] == min && nbVotes == 0){
                scoreMatrix[i]++;
                nbVotes++;
            } else if (nbVotes == 1){
                scoreMatrix[i]--; // si une personne vote pour deux burgers, le vote est caduc
            }
        }
    }
    return scoreMatrix;
}

int *createTableauScoreT2(int **voteTable, int numCols, int numRows, int *tab_gagnant)
{
    int *scoreMatrix;
    scoreMatrix = (int *)malloc(numCols * sizeof(int));

    for (int i = 0; i < numCols; i++)
    {
        scoreMatrix[i] = 0;
    }

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
    printf("\tBurger\tScore\n");
    printf("\t------- --------\n");
    for (int i = 0; i < numCols; i++)
    {
        printf("\t%d\t%d\n", i + 1, tableauScore[i]);
    }
    printf("\n");
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

