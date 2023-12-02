#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include"liste.h"
#include"graphe.h"
#include"lecture_csv.h"
#include"condorcet.h"


int main() {
    printf("TEST GRAPHES : \n");
    Graphe * g = graphe_create();
    Sommet a,b,c;
    a = "A";
    b = "B";
    c = "C";
    graphe_add_sommet(g,a);
    graphe_add_sommet(g,b);
    graphe_add_sommet(g,c);

    graphe_add_sommet(g,a);
    Arete * ar = malloc(sizeof(Arete));
    ar->origine = a;
    ar->arrivee = b;
    ar->poid = 1;
    graphe_add_arete(g,ar);


    printf("nb sommet : %d\n",list_size(g->listeSommets));
    printf("Sommets : %s %s %s\n",(char*)list_at(g->listeSommets,0),(char*)list_at(g->listeSommets,1),(char*)list_at(g->listeSommets,2));

    printf("Arete de %s a %s de poids %d\n",((Arete*)list_at(g->listeAretes,0))->origine,((Arete*)list_at(g->listeAretes,0))->arrivee,((Arete*)list_at(g->listeAretes,0))->poid);

    printf("TEST CONDORCET : \n");

    const char *filename = "VoteJugement.csv";
    Matrix * matrice = malloc(sizeof(matrice));

    countRows(filename,matrice);
    countCols(filename,matrice);

    createMatrix(filename, matrice);

    printMatrix(matrice);

    Matrix * mat_trim = trim_matrix_moodle(matrice);
    printf("Trim : %s\n",mat_trim->data[0][0]);
    printMatrix(mat_trim);
}