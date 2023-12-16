#ifndef VOTE_MAJ_H
#define VOTE_MAJ_H

/**
* @file vote_Majoritaire.c
* @brief Programme pour le jugement majoritaire
* @author Paulin Laurent
*/

int jugementMaj(Matrix *csvMatrix);

int medStatMaj(float* stat);

float* statCandidatJugMaj(int* listCand, int nbElecteur);

int* getVoteCandidat(int **table, int numCand, int nbElecteur);


#endif 