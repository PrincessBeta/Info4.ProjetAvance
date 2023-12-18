#ifndef VOTE_UNINOMINAL_H
#define VOTE_UNINOMINAL_H

#include "lecture_csv.h"
/**
 * @file vote_Uninominal.c
 * @brief Programme principal pour le vote uninominal à deux tours
 * @author Yousra Arroui
 */

int *createTableauScoreT1(int **voteTable, int numCols, int numRows);

int *createTableauScoreT2(int **voteTable, int numCols, int numRows, int *tab_gagnant);
void printTableauScore(int *tableauScore, int numCols);

void findWinnersUni1(int *tableauScore, int numBurgers, int *tab_gagnant);
void findWinnersUni2Tour1(int *tableauScore, int numBurgers, int *tab_gagnant);
int findWinnersUni2Tour2(int *tableauScore, int *tab_gagnant);

#endif
