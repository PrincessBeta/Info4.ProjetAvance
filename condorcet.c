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

Sommet condorcet(Matrix * m,char ** candidats) {
    int verif = 0;
    int i;
    for (i=0;i<m->rows&&!verif;i++) {
        verif = 1;
        for (int j = 0;j<m->cols&&verif;j++) {
            verif = (atoi(m->data[i][j]) >= atoi(m->data[j][i]));
        }
    }
    if (verif) return candidats[i-1];          //i-1 car l'incrémentation a lieu avant le test dans un for, on le fait donc une fois de trop.
    return NULL;                
}


int ind_minimum_ligne(char ** liste,int n) {
    int mini = 0;
    for (int i = 1;i<n;i++) 
        if (atoi(liste[i]) < atoi(liste[mini]) && atoi(liste[i]) != 0) mini = i;
    return mini;
}

Sommet condorcet_minimax(Matrix  * m,char ** candidats) {
    int maxi = 0;
    int col_max = ind_minimum_ligne(m->data[0],m->cols);
    int col;
    for (int i = 1;i<m->rows;i++) {
        col = ind_minimum_ligne(m->data[i],m->cols);
        if (atoi(m->data[i][col]) > atoi(m->data[maxi][col_max])) {
            maxi = i;
            col_max = col;
        }
    }
    printf("maxi : %d %s \n",maxi,candidats[maxi]);

    return candidats[maxi];
}

Graphe * create_graphe_from_matrice(Matrix * m,char ** candidats) {
    Graphe * g = graphe_create();
    for (int i = 0;i<m->rows;i++) {
        for (int j=0;j<m->cols;j++) {
            int duel1 = atoi(m->data[i][j]);
            int duel2 = atoi(m->data[j][i]);
            if (duel1 > duel2) {
                Arete * a = malloc(sizeof(Arete));
                graphe_add_sommet(g,candidats[i]);
                graphe_add_sommet(g,candidats[j]);
                a -> origine = candidats[i];
                a -> arrivee = candidats[j];
                a -> poid = duel1 - duel2;
                graphe_add_arete(g,a);
            }
        }
    }
    return g;
}

Sommet condorcet_paire_decroissante(Matrix * m,char ** candidats) {
    Graphe * graphe_complet = create_graphe_from_matrice(m,candidats);
    Graphe * graphe_reduit = graphe_create();
    graphe_reduit->listeSommets = graphe_complet->listeSommets;
    List * l = tri_liste_arete(graphe_complet->listeAretes);
    for (int i = 0; i<list_size(l); i++) {
        Arete * a = (Arete *) list_at(l,i);
        if (!would_create_cycle(graphe_reduit,a)) graphe_add_arete(graphe_reduit,a);
    }
    
    Sommet s = candidats[0];
    for (int i = 0;i<list_size(graphe_reduit->listeSommets);i++) {
        Arete * a = (Arete *) list_at(l,i);
        if (a->arrivee == s) {
            s = a->origine;
            i = 0;
        }
    };
    return s;
}
