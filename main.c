#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
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
    int methode = -1;
    int useDuelMat= false;  
    bool debug = false;

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
                useDuelMat = true;
                break;
            case 'o':
                {
                int output;
                output = open(optarg,O_WRONLY|O_CREAT,S_IRWXU|S_IRWXO);
                if(-1 == dup2(output,STDOUT_FILENO)){
                    close(output);
                    perror("erreur changement d'output");
                    exit(1);
                }
                debug = true;
                break;
                }
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
    
    int decalage = (useDuelMat) ? 0 : 4;
    int numCols = csvMatrix->cols-decalage;
    int numRows = (csvMatrix->rows)-1;
    if(debug){
        printf("Votes : \n");
        printTable(tableVote,numRows,numCols,"Voteurs","Burgers");

    }
    char* noms_candidats[numCols];
    if (debug) printf("Liste Candidats : \n");
    for (int i = 0; i < numCols; i++)
    {
        noms_candidats[i] = (csvMatrix->data)[0][i+decalage];
        if (debug) printf("%s\n",noms_candidats[i]);
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

        if(debug) {
            printf("Scores : \n");
            printTableauScore(tab_score,numCols);
        }

        printf("Mode de scrutin : Uninomial a un tour, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%\n",
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

        
        if(debug) {
            printf("Scores 1er Tour : \n");
            printTableauScore(tab_score,numCols);
        }
        
        printf("Mode de scrutin : Uninomial a deux tour, tour 1, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%\n",
                numCols,numRows,noms_candidats[tab_gagnant[0]-1],score);

        score = (tab_score[tab_gagnant[1]-1] / (float)numRows)*100;

        printf("Mode de scrutin : Uninomial a deux tour, tour 1, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%\n",
                numCols,numRows,noms_candidats[tab_gagnant[1]-1],score);


        
        tab_score = createTableauScoreT2(tableVote, numCols, numRows, tab_gagnant);
        int winner = findWinnersUni2Tour2(tab_score, tab_gagnant);
        score = (tab_score[winner-1] / (float)numRows)*100;

        if(debug) {
            printf("Scores 2nd Tour : \n");
            printTableauScore(tab_score,numCols);
        }

        printf("Mode de scrutin : Uninomial a deux tour, tour 2, %d candidats, %d votants, vainqueur = %s, score = %2.1f%%\n",
                numCols,numRows,noms_candidats[winner-1],score);

    } 

    if ((methode == JUGEMENT_MAJORITAIRE || methode == TOUTES_METHODES) && !useDuelMat) {
        printf("Mode de scrutin : Jugement majoritaire, %d candidats, %d votants, vainquer = %s\n"
        , numCols, numRows, jugementMaj(tableVote, numCols, numRows, noms_candidats));
    }

    Matrix * matrice_duels;

    if (useDuelMat) {
        matrice_duels = trim_matrix(csvMatrix,1,0);
    } else {
        Matrix * temp = trim_matrix(csvMatrix,1,4);
        matrice_duels = create_matrice_duel(temp);
    }

    if(methode == CONDORCET_MINIMAX || methode == CONDORCET_PAIRES ||
       methode == CONDORCET_SCHULZE || methode == TOUTES_METHODES) {
        if(debug) {
            printf("Matrice Duels :\n");
            printMatrix(matrice_duels);
        }
    }

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
