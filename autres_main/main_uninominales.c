 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"
#include "vote_Uninominal.h"
#include "utils.h"

// main du CC3 càd votes uninominaux.

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
