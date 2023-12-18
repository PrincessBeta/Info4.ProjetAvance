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

int isMethode(char* mtd){
    if(strcmp(mtd, "uni1")==0){
        return 0;
    }
    if(strcmp(mtd, "uni2")==0){
        return 1;
    }
    if(strcmp(mtd, "cm")==0){
        return 2;
    }
    if(strcmp(mtd, "cp")==0){
        return 3;
    }
    if(strcmp(mtd, "cs")==0){
        return 4;
    }
    if(strcmp(mtd, "jm")==0){
        return 5;
    }
    if(strcmp(mtd, "all")==0){
        return 6;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    // Variables for command-line options
    int opt;
    char *inputFile = NULL;
    char *outputFile = NULL;
    int methode = NULL;
    int useDuelMatrix = 0;  // Flag for -d option

    // Process command-line options
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
                useDuelMatrix = 1;
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
    countRows(inputFile, &csvMatrix);
    countCols(inputFile, &csvMatrix);
    createMatrix(inputFile, &csvMatrix);

    int** tableVote = createVoteTable(csvMatrix);
    int numCols = csvMatrix.cols;
    int numRows = csvMatrix.rows-1;
    
    if (useDuelMatrix) {
        Matrix duelMatrix;
        duelMatrix = create_matrice_duel(&csvMatrix);
    }

    if ((methode == 0 || methode == 6) && !useDuelMatrix) {
        int* tab_score;
        int tab_gagnant[numCols];
        for (int i = 0; i < numCols; i++){
            tab_gagnant[i] = 0;
        }
        tab_score = createTableauScoreT1(tableVote, numCols, numRows);
        findWinnersUni1(tab_score, numCols, tab_gagnant);

        printf("Mode de scrutin : uninomial a un tour, %d candidats, 
        %d votants, vainqueur = %s, score: %f/100", );                              
                                        //retravailler uni pour avoir les pourcentages

        printf("\nLe(s) burger(s) gagnant(s) :\n");
        for(int i = 0; i < numCols; i++){
            if(tab_gagnant[i] != 0){
            printf("\nBurger %d\n", tab_gagnant[i]);
            }
        }
    }
    if ((methode == 1 || methode == 6) && !useDuelMatrix) {
        
    } 
    if (methode == 2 || methode == 6) {

    }
    if (methode == 3 || methode == 6) {
    
    }
    if (methode == 4 || methode == 6) {
       
    } 
    if (methode == 5 || methode == 6) {
        
    }

    return 0;
}