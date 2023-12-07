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
#include"utils.h"


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

    const char *filename = "csv/VoteJugement.csv";
    Matrix * matrice = malloc(sizeof(Matrix));

    countRows(filename,matrice);
    countCols(filename,matrice);

    createMatrix(filename, matrice);

    printMatrix(matrice);

    Matrix * mat_trim = trim_matrix(matrice,1,4);
    printMatrix(mat_trim);


    Matrix * zeros = init_matrice_zero(4,4);
    printMatrix(zeros);

    Matrix * mat_duel = create_matrice_duel(mat_trim);
    printMatrix(mat_duel);

    char ** candi = liste_candidat_moodle(matrice->data[0],matrice->cols);

    printf("LE GAGNANT EST : %s\n",condorcet(mat_duel,candi));

    Matrix * m = malloc(sizeof(Matrix));
    countRows(filename,m);
    countCols(filename,m);
    createMatrix("csv/calcul2.csv",m);
    printMatrix(m);
    Matrix * m_trim = trim_matrix(m,1,0);
    printMatrix(m_trim);
    char ** candidats = (m->data)[0];
    printf("Le gagnant est : %s\n",condorcet(m_trim,candidats));
    printf("Le gagnant (minimax) est : %s\n",condorcet_minimax(m_trim,candidats));

    
    for (int i = 0;i<m->cols;i++) candidats[i] = delete_newline(candidats[i]);
    Graphe * graphe = create_graphe_from_matrice(m_trim,candidats);

    printf("nb aretes = %d et nb sommets = %d\n",list_size(graphe->listeAretes),list_size(graphe->listeSommets));

    list_map(graphe->listeSommets,print_string);
    printf("\n");
    list_map(graphe->listeAretes,print_arete);
    printf("Versions triée : \n");
    list_map(tri_liste_arete(graphe->listeAretes),print_arete);
    printf("Le gagnant (paires) est : %s\n",condorcet_paire_decroissante(m_trim,m->data[0]));

    return 0;
}
