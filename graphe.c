#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "graphe.h"
#include "utils.h"



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
        if (a->arrivee == s || a->origine == s) {
            graphe_del_arrete(g,a);
            i--;
        }
    }
    
    list_del_elt(g->listeSommets,s);
    return g;
}


bool rec_search(Graphe * g,Sommet s,Sommet cur,List * parcouru) {
    bool verif = s == cur;
    verif = list_in(parcouru,cur);
    list_push_back(parcouru,cur);
    for (int i = 0;i<list_size(g->listeAretes) && !verif;i++) {
        Arete * a = (Arete *)list_at(g->listeAretes,i);
        if (a->origine == cur) verif = rec_search(g,s,a->arrivee,parcouru);
    }
    return verif;
}

bool depth_search(Graphe * g,Sommet s,Sommet dep) {
    List * parcouru = list_create();
    bool retour = rec_search(g,s,dep,parcouru);
    list_delete(&parcouru);
    return retour;
}

bool would_create_cycle(Graphe * g,Arete * a) {
    return !depth_search(g,a->arrivee,a->origine);
}

List * liste_predecesseur(Graphe * g,Sommet s) {
    List * l = list_create();
    for (int i = 0;i<list_size(g->listeAretes);i++) {
        Arete * a = (Arete *) list_at(g->listeAretes,i);
        if (a->arrivee == s) 
            if (!list_in(l,a->origine)) list_push_front(l,a->origine);
    }
    return l;
}

List * liste_successeur(Graphe * g,Sommet s) {
        List * l = list_create();
    for (int i = 0;i<list_size(g->listeAretes);i++) {
        Arete * a = list_at(g->listeAretes,i);
        if (a->origine == s) 
            if (!list_in(l,a->arrivee)) list_push_front(l,a->arrivee);
    }
    return l;
}
