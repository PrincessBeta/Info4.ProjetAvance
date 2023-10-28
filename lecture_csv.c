#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "lecture_csv.h"
#include <string.h>

int countRows(const char *filename){

    FILE *file = fopen(filename, "r");

    if (file == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier%s\n", filename);
        return -1;
    }

    int rows = 0;
    char *Tab = malloc(MAX_PHRASE_LENGTH * sizeof(char));

    if (Tab == NULL){
        fclose(file);
        return -1;
    }

    while (fgets(Tab, MAX_PHRASE_LENGTH, file) != NULL){
        rows++;
    }

    free(Tab);
    fclose(file);
    return rows;
}


int countCols(const char *filename){

    FILE *file = fopen(filename, "r");

    if (file == NULL){
        return -1;
    }

    int columns = 0;
    char ch;
    int inField = 0;

    while ((ch = fgetc(file)) != EOF){
        if (ch == ','){
            columns++;
        }
        else if (ch == '\n'){
            break;
        }

    }

    fclose(file);
    return columns + 1;
}

Matrix *createMatrix(const char *filename, int nbrows, int nbcolumns){

    char *Tab = malloc(MAX_PHRASE_LENGTH * sizeof(char));

    if (Tab == NULL) {
        return NULL;
    }

    Matrix *matrice = malloc(sizeof(Matrix));
    if (matrice == NULL){
        free(Tab);
        return NULL;
    }

    matrice->rows = nbrows;
    matrice->cols = nbcolumns;

    matrice->data = malloc(nbrows * sizeof(char **));
    if (matrice->data == NULL) {
        free(matrice);
        free(Tab);
        return NULL;
    }

    for (int i = 0; i < nbrows; i++) {
        matrice->data[i] = malloc(nbcolumns * sizeof(char *));
        if (matrice->data[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrice->data[j]);
            }
            free(matrice->data);
            free(matrice);
            free(Tab);
            return NULL;
        }
    }
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        free(Tab);
        for (int i = 0; i < nbrows; i++) {
            free(matrice->data[i]);
        }
        free(matrice->data);
        free(matrice);
        return NULL;
    }

    for (int i = 0; i < nbrows; i++)
    {
        if (fgets(Tab, MAX_PHRASE_LENGTH, file) == NULL)
        {
            break;
        }

        char *token = strtok(Tab, ",");
        int j = 0;

        while (token != NULL && j < nbcolumns) {   
            matrice->data[i][j] = strdup(token);
            if (matrice->data[i][j] == NULL) {
                for (int k = 0; k <= j; k++) {
                    free(matrice->data[i][k]);
                }
                free(Tab);
                fclose(file);
                return NULL;
            }

            token = strtok(NULL, ",");
            j++;
        }
    }

    free(Tab);
    fclose(file);
    return matrice;
}

void printMatrix(Matrix *matrix, int nbrows, int nbcolumns){
    for (int j = 0; j < nbcolumns; j++) {
        if (matrix->data[0][j] != NULL) {
            printf("%s\t", matrix->data[0][j]);
        }
    }
    printf("\n");

    // Afficher les données à partir de la deuxième ligne
    for (int i = 1; i < nbrows; i++) {
        for (int j = 0; j < nbcolumns; j++) {
            if (matrix->data[i][j] != NULL) {
                printf("%s\t", matrix->data[i][j]);
            }
        }
        printf("\n");
    }  
}

void freeMatrix(Matrix *matrix, int nbrows, int nbcolumns) {
    for (int i = 0; i < nbrows; i++) {
        for (int j = 0; j < nbcolumns; j++) {
            if (matrix->data[i][j] != NULL) {
                free(matrix->data[i][j]);
            }
        }
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}



