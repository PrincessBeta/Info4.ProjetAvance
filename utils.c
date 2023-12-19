#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lecture_csv.h"
#include "sha256_utils.h"
#include "liste.h"
#include "graphe.h"

void uppercase(char* string){
    for (unsigned int i = 0; i < strlen(string); i++)
    {
        string[i] = toupper(string[i]);
    }
}

void formatName(char* string){
    for (unsigned int i = 0; i < strlen(string); i++)
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
    Matrix matrix;
    createMatrix(filename,&matrix);

    for (int i = 0; i < matrix.rows; i++)
    {
        if (strncmp(matrix.data[i][0], num_etu,8) == 0)
        {
            strcpy(code,&(matrix.data[i][0][9]));
            strtok(code,"\n");
            freeMatrix(&matrix);
            return;
        }
        
    }
    
}


int **createVoteTable(Matrix *csvMatrix){
    int **voteTable;

    if (csvMatrix == NULL || csvMatrix->data == NULL){
        fprintf(stderr, "Erreur : Matrice CSV invalide\n");
        exit(1);
    }
    voteTable = (int **)malloc(csvMatrix->rows * sizeof(int *));

    if (voteTable == NULL){
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice de votes\n");
        exit(1);
    }

    int numCols = 10;
    for (int i = 1; i < csvMatrix->rows; i++){
        voteTable[i - 1] = (int *)malloc(numCols * sizeof(int));

        if (voteTable[i - 1] == NULL){
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la ligne %d de la matrice de votes\n", i);
            exit(1);
        }
        for (int j = 4; j < csvMatrix->cols; j++){
            voteTable[i - 1][j - 4] = atoi(csvMatrix->data[i][j]);
        }
    }
    return voteTable;
}

void printTable(int **table, int numRows, int numCols, const char *rowLabel, const char *colLabel)
{
    printf("\t%s\t", colLabel);
    for (int j = 0; j < numCols; j++)
    {
        printf("%2d\t", j + 1);
    }
    printf("\n");

    printf("\t");
    for (int j = 0; j <= numCols; j++)
    {
        printf("--------");
    }
    printf("\n");

    for (int i = 0; i < numRows; i++)
    {
        printf("%s %2d |\t", rowLabel, i + 1);

        for (int j = 0; j < numCols; j++)
        {
            printf("%2d\t", table[i][j]);
        }

        printf("\n");
    }
    printf("\n");
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

    Matrix matrix;
    createMatrix(filename,&matrix);
    strcpy(votes,"");

    for (int i = 4; i < matrix.rows; i++)
    {
        if (strcmp(matrix.data[i][3],key) == 0) {
            for (int j = 4; j < 14; j++)
            {
                strcat(votes,matrix.data[i][j]);
                strcat(votes," ");
            }
        }
    }
    freeMatrix(&matrix);
    
}

char * itoa(int x){
    int length = snprintf( NULL, 0, "%d", x );
    char* str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", x );
    return str;
}

Matrix * init_matrice_zero(int l,int c) {
    Matrix * mat = malloc(sizeof(Matrix));
    mat->rows = l;
    mat->cols = c;
    mat->data = malloc(l * sizeof(char **));
    for (int i=0;i<l;i++)
        mat->data[i] = malloc(sizeof(char*)*c);
    
    for (int i = 0; i<l ;i++)
        for (int j =0; j<c; j++)
            mat->data[i][j] = "0";

    return mat;
}


Matrix * trim_matrix(Matrix * m,int lig,int col) {
    Matrix * new_mat = malloc(sizeof(Matrix));
    new_mat->data = malloc((m->rows-lig) * sizeof(char **));
    for (int i=0;i<m->rows-lig;i++)
        new_mat->data[i] = malloc(sizeof(char*)*(m->cols-col));
    new_mat->rows = m->rows-lig;
    new_mat->cols = m->cols-col;
    for (int i = 0;i<m->rows-lig;i++) {
        for (int j = 0;j<m->cols-col;j++) {
            new_mat->data[i][j] = m->data[i+lig][j+col];
        }
    }
    return new_mat;
}

char ** liste_candidat_moodle(char ** tab,int n) {
    char ** new_tab = malloc((n-4)*sizeof(char*));
    for (int i=0;i<n-4;i++) {
        new_tab[i] = delete_newline(tab[i+4]);
    }
    return new_tab;
}

void * print_int(void * n) {
    printf("%d",*(int*)n);
    return n;
}

void * print_string(void * s) {
    printf("%s",(char *)s);
    return s;
}


void * print_arete(void * aret) {
    Arete * a = (Arete *)aret;
    printf("Arete de %s a %s de poids %d\n",a->origine,a->arrivee,a->poid);
    return aret;
}

char * delete_newline(char * s) {
    int len = strlen(s);
    if (s[len-1] == '\n') s[len-1] = '\0'; 
    return s;
}


List * inserer_liste_triee(List * l,Arete * a) {
    bool verif = true;
    for (int i = 0;i<list_size(l)&&verif;i++) {
        Arete * arete = (Arete *) list_at(l,i);
        if (arete->poid < a->poid) {
            verif = false;
            list_insert_at(l,i,a);
        }
    }
    if (verif) list_push_back(l,a);
    return l;
}

List * tri_liste_arete(List * l){
    List * liste_triee = list_create();
    for (int i = 0;i<list_size(l);i++) inserer_liste_triee(liste_triee,list_at(l,i));
    return liste_triee;
}
