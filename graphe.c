#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "graphe.h"



Graphe * graphe_create() {
    Graphe * g = malloc(sizeof(Graphe));
    g -> listeAretes = list_create();
    g -> listeSommets = list_create();
    return g;
}

void graphe_delete(Graphe *g) {
    list_delete(&(g -> listeAretes));
    list_delete(&(g -> listeSommets));
    free(g);
}

Graphe * graphe_add_sommet(Graphe *g,Sommet s){
    if (!list_in(g->listeSommets,s))
        list_push_back(g ->listeSommets,s);
    return g;
}

Graphe * graphe_add_arete(Graphe * g,Arete * a) {
    if (list_in(g->listeSommets,a->origine) && list_in(g->listeSommets,a->arrivee)) {
        list_push_back(g->listeAretes,a);
    }
    return g;
}

Graphe * graphe_del_arrete(Graphe * g,Arete * a) {
    list_del_elt(g->listeAretes,a);
    return g;
}


Graphe * graphe_del_sommet(Graphe * g,Sommet s) {
    for (int i = 0;i<list_size(g->listeAretes);i++) {
        Arete * a = list_at(g->listeAretes,i);
        if (a->arrivee == s || a->origine == s) graphe_del_arrete(g,a);
    }
    list_del_elt(g->listeSommets,s);
    return g;
}

bool would_create_cycle(Graphe * g,Arete * a) {
    bool verif = true;
    for (int i = 0;i<list_size(g->listeAretes) && verif;i++)
        verif = ((Arete *)list_at(g->listeAretes,i))->origine == a ->arrivee;
    return verif;
}

