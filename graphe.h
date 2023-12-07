#ifndef GRAPHE_H
#define GRAPHE_H


typedef char * Sommet;

typedef struct arete_s {
    Sommet origine;
    Sommet arrivee;
    int poid;
} Arete;


typedef struct graphe_s {
    List * listeSommets;
    List * listeAretes;
} Graphe;


/// \brief Crée et retourne un graphe vide.
/// \author Raphaël Rumin
/// \date 02/12/2023
Graphe * graphe_create();

/// \brief Suprrime le graphe et libère la mémoire.
/// \author Raphaël Rumin
/// \date 02/12/2023
void graphe_delete(Graphe *g);

/// \brief Ajoute un sommet au graphe si il n'y est pas déjà.
/// \author Raphaël Rumin
/// \date 02/12/2023
Graphe * graphe_add_sommet(Graphe *g,Sommet s);

/// \brief Ajoute une arête au graphe si ses 2 extrémités appartiennent au graphe.
/// \author Raphaël Rumin
/// \date 02/12/2023
Graphe * graphe_add_arete(Graphe * g,Arete * a);

/// \brief Supprime une arête du graphe.
/// \author Raphaël Rumin
/// \date 02/12/2023
Graphe * graphe_del_arrete(Graphe * g,Arete * a);

/// \brief Supprime un sommet et toutes les arêtes reliées.
/// \author Raphaël Rumin
/// \date 02/12/2023
Graphe * graphe_del_sommet(Graphe * g,Sommet s);

/// \brief Vérifie si l'ajout de l'arête crée un cycle dans un graphe n'en contenant pas.
/// \author Raphaël Rumin
/// \date 05/12/2023
bool would_create_cycle(Graphe * g,Arete * a);


#endif