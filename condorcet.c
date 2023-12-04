#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include"liste.h"
#include"graphe.h"
#include"lecture_csv.h"
#include"condorcet.h"
#include"utils.h"




Matrix * create_matrice_duel(Matrix * m) {
    Matrix * mat_duel = init_matrice_zero(m->cols,m->cols);

    for (int i = 0;i<m->rows;i++) {
        for (int j1 = 0;j1<m->cols;j1++) {
            for (int j2 = 0;j2<m->cols;j2++) {
                if (strcmp(m->data[i][j1],"-1") != 0 && (atoi(m->data[i][j1]) < atoi(m->data[i][j2]) || strcmp(m->data[i][j2],"-1") == 0)) {
                    // -1 est le cas ou l'on n'a pas donné une note a un candidat.
                    int x = atoi(mat_duel->data[j1][j2]) + 1;
                    mat_duel->data[j1][j2] = itoa(x);
                }
            }
        }
    }
    return mat_duel;
}

int condorcet(Matrix * m) {
    int verif = 0;
    int i;
    for (i=0;i<m->rows&&!verif;i++) {
        verif = 1;
        for (int j = 0;j<m->cols&&verif;j++) {
            verif = (atoi(m->data[i][j]) >= atoi(m->data[j][i]));
        }
    }
    if (verif) return i-1;          //i-1 car l'incrémentation a lieu avant le test dans un for, on le fait donc une fois de trop.
    return -1;                
}