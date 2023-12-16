#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "lecture_csv.h"
#include "vote_Majoritaire.h"
#include "utils.h"

int main(int argc, char **argv){

    if (argc!=2){
        perror("nombres d'entrées incorrect");
        exit(1);
    }

    const char *filename = argv[1];
    Matrix matrice;
    countRows(filename, &matrice);
    countCols(filename, &matrice);
    createMatrix(filename, &matrice);

    int **voteTable = createVoteTable(&matrice);

    printTable(voteTable, matrice.rows-1, 10, "electeur", "candidat");

    printf("\n\n\n\n");
    printf("le burger vainqueur est : %d\n",jugementMaj(&matrice));
}