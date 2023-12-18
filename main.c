#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "lecture_csv.h"
#include "vote_Uninominal.h"
#include "condorcet_schulze.h"
#include "condorcet.h"
#include "vote_Majoritaire.h"
#include "utils.h"
#include "liste.h"

#define UNINOMINAL_1 0
#define UNINOMINAL_2 1
#define CONDORCET_MINIMAX 2
#define CONDORCET_PAIRES 3
#define CONDORCET_SCHULZE 4
#define JUGEMENT_MAJORITAIRE 5
#define TOUTES_METHODES 6



int isMethode(char* mtd){
    if(strcmp(mtd, "uni1")==0){
        return UNINOMINAL_1;
    }
    if(strcmp(mtd, "uni2")==0){
        return UNINOMINAL_2;
    }
    if(strcmp(mtd, "cm")==0){
        return CONDORCET_MINIMAX;
    }
    if(strcmp(mtd, "cp")==0){
        return CONDORCET_PAIRES;
    }
    if(strcmp(mtd, "cs")==0){
        return CONDORCET_SCHULZE;
    }
    if(strcmp(mtd, "jm")==0){
        return JUGEMENT_MAJORITAIRE;
    }
    if(strcmp(mtd, "all")==0){
        return TOUTES_METHODES;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int opt;
    char *inputFile = NULL;
    char *outputFile = NULL;
    int methode = -1;
    int useDuelMat= 0;  

    while ((opt = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (opt) {
            case 'i':
                if (inputFile!=NULL){
                    fprintf(stderr, "-i et -d ne peuvent pas etre choisi en meme temps\n");
                    return 0;
                }
                inputFile = optarg;
                break;
            case 'd':
                if (inputFile!=NULL){
                    fprintf(stderr, "-i et -d ne peuvent pas etre choisi en meme temps\n");
                    return 0;
                }
                inputFile = optarg;
                useDuelMat = 1;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'm':
                methode = isMethode(optarg);
                if (methode == -1){
                    fprintf(stderr, "methode non valide\n");
                    return 0;
                }
                break;
            default:
                fprintf(stderr, "Utilisation: %s [-i nomFichier.csv] [-d nomFichier.csv] [-o nomFichier.txt] [-m methode]\n", argv[0]);
                return 0;
        }
    }

    if (inputFile == NULL) {
        fprintf(stderr, "-i ou -d est necessaire\n");
        return 0;
    }

    Matrix csvMatrix;
    createMatrix(inputFile, &csvMatrix);

    int** tableVote = createVoteTable(csvMatrix);
    int numCols = csvMatrix.cols;
    int numRows = csvMatrix.rows-1;
    
    if (useDuelMat) {
        Matrix duelMatrix;
        duelMatrix = create_matrice_duel(&csvMatrix);
    }

    char** candi = (csvMatrix->data)[0];
/*
    if ((methode == UNINOMINAL_1 || methode == TOUTES_METHODES) && !useDuelMat) {
        int* tab_score;
        int tab_gagnant[numCols];
        for (int i = 0; i < numCols; i++){
            tab_gagnant[i] = 0;
        }
        tab_score = createTableauScoreT1(tableVote, numCols, numRows);
        findWinnersUni1(tab_score, numCols, tab_gagnant);

        printf("Mode de scrutin : Uninomial a un tour, %d candidats, %d votants, vainqueur = %s, score = %f/100",
                numCols,numRows,candi[tab_gagnant[0]],tab_score[tab_gagnant[0]]);

        printf("\nLe(s) burger(s) gagnant(s) :\n");
        for(int i = 0; i < numCols; i++){
            if(tab_gagnant[i] != 0){
            printf("\nBurger %d\n", tab_gagnant[i]);
            }
        }
    }

    if ((methode == UNINOMINAL_2 || methode == TOUTES_METHODES) && !useDuelMat) {
        int* tab_score;
        int tab_gagnant[numCols];
        for (int i = 0; i < numCols; i++){
            tab_gagnant[i] = 0;
        }

        tab_score = createTableauScoreT1(tableVote, numCols, numRows);
        findWinnersUni2Tour1(tab_score, numCols, tab_gagnant);

        for (int i=0; i<tab_gagnant.length; i++);
        
        printf("Mode de scrutin : Uninomial a deux tour, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f/100",
                numCols,numRows,candi[tab_gagnant[0]],tab_score[tab_gagnant[0]]);

        printf("Mode de scrutin : Uninomial a deux tour, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f/100",
                numCols,numRows,candi[tab_gagnant[1]],tab_score[tab_gagnant[1]]);


        
        tab_score = createTableauScoreT2(tableVote, numCols, numRows, tab_gagnant);
        int winner = findWinnersUni2Tour2(tab_score, tab_gagnant);

        printf("Mode de scrutin : Uninomial a deux tour, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f/100",
                numCols,numRows,candi[winner],tab_score[winner]);

        
    } */
    if (methode == CONDORCET_MINIMAX || methode == TOUTES_METHODES) {
        Matrix * m_trim = trim_matrix(csvMatrix,1,0);
        printf("Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s\n",numCols, numRows, condorcet_minimax(m_trim, candi));
    }
    if (methode == CONDORCET_PAIRES || methode == TOUTES_METHODES) {
        Matrix * m_trim = trim_matrix(csvMatrix,1,0);
        printf("Mode de scrutin : Condorcet paire, %d candidats, %d votants, vainqueur = %s\n",numCols, numRows, condorcet_paire_decroissante(m_trim, candi));
    }
    if (methode == CONDORCET_SCHULZE || methode == TOUTES_METHODES) {
        Matrix * m_trim = trim_matrix(csvMatrix,1,0);
        printf("Mode de scrutin : Condorcet schulze, %d candidats, %d votants, vainqueur = %s\n",numCols, numRows, condorcet_schulze(m_trim, candi));
    } 
    if (methode == JUGEMENT_MAJORITAIRE || methode == TOUTES_METHODES) {
        printf("Mode de scrutin : Jugement majoritaire, %d candidats, %d votants, vainquer = %s\n", numCols, numRows, jugementMaj(tableVote, numCols, numRows, candi));
    }

    return 0;
}