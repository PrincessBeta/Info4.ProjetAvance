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
    // char *outputFile = NULL;
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
                // outputFile = optarg;
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

    Matrix *csvMatrix = malloc(sizeof(Matrix));
    createMatrix(inputFile, csvMatrix);

    int** tableVote = createVoteTable(csvMatrix);
    int numCols = csvMatrix->cols-4;
    int numRows = (csvMatrix->rows)-1;
    char* noms_candidats[numCols];
    for (int i = 0; i < numCols; i++)
    {
        noms_candidats[i] = (csvMatrix->data)[0][i+4];
    }

    if ((methode == UNINOMINAL_1 || methode == TOUTES_METHODES) && !useDuelMat) {
        int* tab_score;
        int tab_gagnant[numCols];
        for (int i = 0; i < numCols; i++){
            tab_gagnant[i] = 0;
        }
        tab_score = createTableauScoreT1(tableVote, numCols, numRows);
        findWinnersUni1(tab_score, numCols, tab_gagnant);
        float score = (tab_score[tab_gagnant[0]-1] / (float)numRows)*100;
        printTableauScore(tab_score,numCols);

        printf("Mode de scrutin : Uninomial a un tour, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%",
                numCols,numRows,noms_candidats[tab_gagnant[0]-1],score);

    }

    if ((methode == UNINOMINAL_2 || methode == TOUTES_METHODES) && !useDuelMat) {
        int* tab_score;
        int tab_gagnant[numCols];
        for (int i = 0; i < numCols; i++){
            tab_gagnant[i] = 0;
        }

        tab_score = createTableauScoreT1(tableVote, numCols, numRows);
        findWinnersUni2Tour1(tab_score, numCols, tab_gagnant);
        float score = (tab_score[tab_gagnant[0]-1] / (float)numRows)*100;

        
        printf("Mode de scrutin : Uninomial a deux tour, tour 1, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%\n",
                numCols,numRows,noms_candidats[tab_gagnant[0]-1],score);

        score = (tab_score[tab_gagnant[1]-1] / (float)numRows)*100;

        printf("Mode de scrutin : Uninomial a deux tour, tour 1, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%\n",
                numCols,numRows,noms_candidats[tab_gagnant[1]-1],score);


        
        tab_score = createTableauScoreT2(tableVote, numCols, numRows, tab_gagnant);
        int winner = findWinnersUni2Tour2(tab_score, tab_gagnant);
        score = (tab_score[winner-1] / (float)numRows)*100;

        printf("Mode de scrutin : Uninomial a deux tour, tour 2, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%\n",
                numCols,numRows,noms_candidats[winner-1],score);

        
    } 

    if (methode == JUGEMENT_MAJORITAIRE || methode == TOUTES_METHODES) {
        printf("Mode de scrutin : Jugement majoritaire, %d candidats, %d votants, vainquer = %s\n"
        , numCols, numRows, jugementMaj(tableVote, numCols, numRows, noms_candidats));
    }

    Matrix* matrice_duels = (useDuelMat) ? csvMatrix : 
                                            create_matrice_duel(trim_matrix(csvMatrix,1,4));

    if (methode == CONDORCET_MINIMAX || methode == TOUTES_METHODES) {
        printf("Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s\n"
        ,numCols, numRows, condorcet_minimax(matrice_duels, noms_candidats));
    }

    if (methode == CONDORCET_PAIRES || methode == TOUTES_METHODES) {
        printf("Mode de scrutin : Condorcet paire, %d candidats, %d votants, vainqueur = %s\n"
        ,numCols, numRows, condorcet_paire_decroissante(matrice_duels, noms_candidats));
    }

    if (methode == CONDORCET_SCHULZE || methode == TOUTES_METHODES) {
        List* res = condorcet_schulze(matrice_duels, noms_candidats);
        printf("Mode de scrutin : Condorcet schulze, %d candidats, %d votants, vainqueur = "
        ,numCols, numRows );
        for (int i = 0; i < res->size; i++)
        {
            printf("%s ", (char*)list_at(res,i));
        }
        printf("\n");
        
    } 

    return 0;
}