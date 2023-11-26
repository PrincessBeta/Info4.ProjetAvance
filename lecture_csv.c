
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "lecture_csv.h"
#include <string.h>

void countRows(const char *filename,Matrix *matrice){

    FILE *file = fopen(filename, "r");

    if (file == NULL){
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }

    int ligne = 0;
    char *Tab = malloc(MAX_PHRASE_LENGTH * sizeof(char));

    if (Tab == NULL){
        fclose(file);
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire\n");
        exit(1);
    }

    while (fgets(Tab, MAX_PHRASE_LENGTH, file) != NULL){
        ligne++;
    }

    free(Tab);
    fclose(file);
    matrice->rows=ligne;
}


void countCols(const char *filename,Matrix *matrice){

    FILE *file = fopen(filename, "r");

    if (file == NULL){
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }

    //changé de 0 a 1 par Yael
    int columns = 1;
    char ch;

    while ((ch = fgetc(file)) != EOF){
        if (ch == ','){
            columns++;
        }
        else if (ch == '\n'){
            break;
        }
    }

    fclose(file);
    matrice->cols = columns;
}

void createMatrix(const char *filename, Matrix *matrice){
    
    //ajouté par Yael le 22/11/23 pour rendre le code plus lisible.
    countCols(filename,matrice);
    countRows(filename,matrice);
    char *Tab = malloc(MAX_PHRASE_LENGTH * sizeof(char));

    if (Tab == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire\n");
        exit(1);
    }
    
    
    if (matrice == NULL){
        free(Tab);
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la matrice\n");
        exit(1);
    }
    
    matrice->data = malloc(matrice->rows * sizeof(char **));
    if (matrice->data == NULL) {
        free(matrice);
        free(Tab);
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire\n");
        exit(1);
    }
    
    for (int i = 0; i < matrice->rows; i++) {
        matrice->data[i] = malloc((matrice->cols) * sizeof(char *));
        if (matrice->data[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrice->data[j]);
            }
            free(matrice->data);
            free(matrice);
            free(Tab);
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire\n");
            exit(1);
        }
    }
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        free(Tab);
        for (int i = 0; i < matrice->rows; i++) {
            free(matrice->data[i]);
        }
        free(matrice->data);
        free(matrice);
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < matrice->rows; i++)
    {
        if (fgets(Tab, MAX_PHRASE_LENGTH, file) == NULL)
        {
            break;
        }

        char *token = strtok(Tab, ",");
        int j = 0;

        while (token != NULL && j < matrice->cols) {   
            matrice->data[i][j] = strdup(token);
            if (matrice->data[i][j] == NULL) {
                for (int k = 0; k <= j; k++) {
                    free(matrice->data[i][k]);
                }
                free(Tab);
                fclose(file);
                fprintf(stderr, "Erreur : Échec de l'allocation mémoire\n");
                exit(0);
            }

            token = strtok(NULL, ",");
            j++;
        }
    }

    free(Tab);
    fclose(file);
}

void printMatrix(Matrix *matrice){
    for (int j = 0; j < matrice->cols; j++) {
        if (matrice->data[0][j] != NULL) {
            printf("%s\t", matrice->data[0][j]);
        }
    }
    printf("\n");

    for (int i = 1; i < matrice->rows; i++) {
        for (int j = 0; j < matrice->cols; j++) {
            if (matrice->data[i][j] != NULL) {
                printf("%s\t", matrice->data[i][j]);
            }
        }
        printf("\n");
    }  
}

void freeMatrix(Matrix *matrice) {
    for (int i = 0; i < matrice->rows; i++) {
        for (int j = 0; j < matrice->cols; j++) {
            if (matrice->data[i][j] != NULL) {
                free(matrice->data[i][j]);
            }
        }
        free(matrice->data[i]);
    }
    free(matrice->data);
    matrice->data = NULL;
}



