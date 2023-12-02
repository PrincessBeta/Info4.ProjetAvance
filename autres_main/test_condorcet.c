#include "graphe.h"
#include "liste.h"
#include <stdio.h>



int main() {
    Graphe * g = graphe_create();
    graphe_add_sommet(g,"ABC") ;

    printf("nb sommet : %d\n",list_size(g->listeAretes));

    graphe_add_sommet(g,"DEF") ;
    graphe_add_sommet(g,"GHI") ;

    printf("nb sommet : %d\n",list_size(g->listeAretes));

    graphe_add_sommet(g,"ABC") ;
    Arete a = {"ABC","DEF",1};
    graphe_add_arete(g,a);

    printf("nb sommet : %d\n",list_size(g->listeAretes));
    printf("Sommets : %s %s %s\n",list_at(g->listeSommets,0),list_at(g->listeSommets,1),list_at(g->listeSommets,2));

    printf("Arete de %s a %s de poids %d\n",list_at(g->listeAretes,0).origine,list_at(g->listeAretes,0).arrivee,list_at(g->listeAretes,0).poid)
}