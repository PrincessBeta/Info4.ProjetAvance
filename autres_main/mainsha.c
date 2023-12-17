#include <stdio.h>
#include "lecture_csv.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

int main(int argc,const char* argv[]) {
    if (argc != 5) { // test de l'usage
        perror("Usage : sha256 type_de_vote nom prenom num_etudiant, all in lowercase \n");
        exit(1);
    }

    //treating the input
    const char* voteType = argv[1];
    char* nom = malloc(MAX_NAME_SIZE*sizeof(char));
    char* prenom= malloc(MAX_NAME_SIZE*sizeof(char));
    char* numEtu= malloc(MAX_NAME_SIZE*sizeof(char));
    strcpy(nom,argv[2]);
    strcpy(prenom,argv[3]);
    strcpy(numEtu,argv[4]);

    char* votes = malloc(MAX_NAME_SIZE*sizeof(char));
    getVotes(nom,prenom,numEtu,voteType,votes);
    printf("%s %s : %s \n",nom,prenom,votes);

  
    return 0; // Return 0 to indicate success
}