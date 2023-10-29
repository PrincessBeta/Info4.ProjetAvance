#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lecture_csv.h"
#include "sha256_utils.h"

void uppercase(char* string){
    for (int i = 0; i < strlen(string); i++)
    {
        string[i] = toupper(string[i]);
    }
}

void formatName(char* string){
    for (int i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
    string[0] = toupper(string[0]);
    
}

void getCode(char* num_etu, char* code,const char* voteType){
    char* voteTypeAlt = malloc(MAX_NAME_SIZE*sizeof(char));
    char* filename = malloc(MAX_NAME_SIZE*sizeof(char));
    strcpy(voteTypeAlt,voteType);
    formatName(voteTypeAlt);
    strcpy(filename,"code");
    strcat(filename,voteTypeAlt);
    strcat(filename,"NumEtu.csv");

    Matrix *matrix;
    createMatrix(filename,matrix);

    for (int i = 0; i < matrix->rows; i++)
    {
        if (strncmp(matrix->data[i][0], num_etu,8) == 0)
        {
            strcpy(code,&(matrix->data[i][0][9]));
            strtok(code,"\n");
            freeMatrix(matrix);
            return;
        }
        
    }
    
}

char* getUncrpytedKey(char* surname, char* name, char* num_etu,const char* voteType){
    int uncrypted_key_size = strlen(surname) + 1 + strlen(name) + strlen(num_etu)+1;
    char* uncrypted_key = malloc(sizeof(char)*uncrypted_key_size); 
    char* code = malloc(MAX_NAME_SIZE*sizeof(char));

    uppercase(surname);
    strcpy(uncrypted_key,surname);
    strcat(uncrypted_key," ");
    formatName(name);
    strcat(uncrypted_key,name);
    getCode(num_etu,code,voteType);
    strcat(uncrypted_key,code);
    return uncrypted_key;
}

void encryptKey(char* uncrypted_key,char hashRes[SHA256_BLOCK_SIZE*2+1]){
    sha256ofString((BYTE*)uncrypted_key,hashRes);
}

void getVotes(char* surname, char* name, char* num_etu,const char* voteType, char* votes){
    char* uncrypted_key = getUncrpytedKey(surname,name,num_etu,voteType);
    char key[SHA256_BLOCK_SIZE*2+1];
    encryptKey(uncrypted_key,key);

    char* filename = malloc(MAX_NAME_SIZE*sizeof(char));
    char* voteTypeAlt = malloc(MAX_NAME_SIZE*sizeof(char));
    strcpy(voteTypeAlt,voteType);
    formatName(voteTypeAlt);
    strcpy(filename,"Vote");
    strcat(filename,voteTypeAlt);
    strcat(filename,".csv");

    Matrix *matrix;
    createMatrix(filename,matrix);
    strcpy(votes,"");

    for (int i = 4; i < matrix->rows; i++)
    {
        if (strcmp(matrix->data[i][3],key) == 0) {
            for (int j = 4; j < 14; j++)
            {
                strcat(votes,matrix->data[i][j]);
                strcat(votes," ");
            }
        }
    }
    freeMatrix(matrix);
    
}
