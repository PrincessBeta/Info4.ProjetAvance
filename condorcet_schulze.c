#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "condorcet_schulze.h"
#include "condorcet.h"
#include "liste.h"
#include "graphe.h"
#include "utils.h"
#include "lecture_csv.h"




bool appartient_groupe_tete(Graphe * g,Sommet s,List * tete) {
    bool verif = true;
    for (int i = 0;i<list_size(tete) && verif;i++) {
        verif = depth_search(g,(Sommet)list_at(tete,i),s);
    }
    return verif;
}

List * groupe_tete(Graphe * g,Sommet s) {
    List * tete = list_create();
    list_push_back(tete,s);
    List * a_parcourir = liste_predecesseur(g,s);
    while (!list_is_empty(a_parcourir)) {
        Sommet cur = (Sommet) list_at(a_parcourir,0);
        list_pop_front(a_parcourir);
        List * pred = liste_predecesseur(g,cur);
        if (!list_in(tete,cur)) list_push_back(tete,cur);
        for (int i = 0;i<list_size(pred);i++) {
            Sommet som = list_at(pred,i);
            if (!list_in(tete,som)) list_push_back(a_parcourir,som); 
        }
        
    }
    return tete;
}

bool in_liste_liste(List * liste,void * e) {
    bool verif = false;
    for (int j = 0;j<list_size(liste) && !verif;j++) {
        List * l = list_at(liste,j);
        verif = list_in(l,e);
    }
    return verif;
}

List * ajouter_liste_dans_liste_liste(List * liste,List * ajout) {
    bool contenue = false;
    for (int j = 0;j<list_size(liste) && !contenue;j++) {
        List * l = list_at(liste,j);
        contenue = list_contain_list(l,ajout) && list_contain_list(ajout,l);
    }
    if (!contenue) list_push_back(liste,ajout);
    return liste;
}

Graphe * suppression_schwartz(Graphe * g,List * tete) {
    for (int i = 0;i<list_size(g->listeSommets);i++) {
        Sommet s = list_at(g->listeSommets,i);
        if (!in_liste_liste(tete,s)) {
            graphe_del_sommet(g,s);
            i--;
        }
    }
    return g;
}

List * tete_minimale(List * liste_groupes_tete) {
    List * liste_tete_minimale = list_create();
    list_push_front(liste_tete_minimale,list_at(liste_groupes_tete,0));
    int min = list_size(list_at(liste_groupes_tete,0));
    for (int i = 1;i<list_size(liste_groupes_tete);i++) {
        List * cur = (List *) list_at(liste_groupes_tete,i);
        if (list_size(cur) == min) {
            ajouter_liste_dans_liste_liste(liste_tete_minimale,cur);
        } else if (list_size(cur) < min) {
            for (int j = 0;j<list_size(liste_tete_minimale);j++) list_pop_front(liste_tete_minimale);
            list_push_front(liste_tete_minimale,cur); 
        }
    }
    return liste_tete_minimale;
}

List * condorcet_schulze(Matrix * m,char ** candidats) {
    List * liste_groupes_tete = list_create();
    Graphe * g = create_graphe_from_matrice(m,candidats);

    g->listeAretes = tri_liste_arete(g->listeAretes);


    while (list_size(g->listeAretes) != 0) {

        
        for (int i = 0;i<list_size(g->listeSommets);i++) {
            Sommet s = (Sommet) list_at(g->listeSommets,i);
            list_push_back(liste_groupes_tete,groupe_tete(g,s));
        }


        List * liste_tete_minimale = tete_minimale(liste_groupes_tete);


        suppression_schwartz(g,liste_tete_minimale);


        if (list_size(g->listeAretes) > 0) list_pop_back(g->listeAretes);
    }

    return g->listeSommets;
}
