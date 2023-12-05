#ifndef CONDORCET_H
#define CONDORCET_h

/// \brief Retourne une matrice de duel à partir d'une matrice de résultats de Condorcet.
/// \author Raphaël Rumin
/// \date 04/12/2023
Matrix * create_matrice_duel(Matrix * m);


/// \brief Retourne le gagant de Condorcet à partir de la matrice de duel. Retourne -1 en cas de paradoxe de Condorcet.
/// \author Raphaël Rumin
/// \date 04/12/2023
int condorcet(Matrix * m);

/// \brief Retourne le gagant de Condorcet à partir de la matrice de duel avec la méthode minimax.
/// \author Raphaël Rumin
/// \date 05/12/2023
int condorcet_minimax(Matrix * m);

/// \brief Retourne la matrice créée à partir de la matrice de duel et de la liste des candidats.
/// \author Raphaël Rumin
/// \date 05/12/2023
Graphe * create_graphe_from_matrice(Matrix * m,char ** candidats);

#endif

