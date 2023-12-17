#ifndef CONDORCET_H
#define CONDORCET_H

/// \brief Retourne une matrice de duel à partir d'une matrice de résultats de Condorcet.
/// \author Raphaël Rumin
/// \date 04/12/2023
Matrix * create_matrice_duel(Matrix * m);


/// \brief Retourne le gagant de Condorcet à partir de la matrice de duel. Retourne null en cas de paradoxe de Condorcet.
/// \author Raphaël Rumin
/// \date 04/12/2023
Sommet condorcet(Matrix * m,char ** candidats);

/// \brief Retourne le gagant de Condorcet à partir de la matrice de duel avec la méthode minimax.
/// \author Raphaël Rumin
/// \date 05/12/2023
Sommet condorcet_minimax(Matrix * m,char ** candidats);

/// \brief Retourne la matrice créée à partir de la matrice de duel et de la liste des candidats.
/// \author Raphaël Rumin
/// \date 05/12/2023
Graphe * create_graphe_from_matrice(Matrix * m,char ** candidats);

/// \brief Retourne le gagant de Condorcet à partir de la matrice de duel avec la méthode des paires décroissantes.
/// \author Raphaël Rumin
/// \date 06/12/2023
Sommet condorcet_paire_decroissante(Matrix * m,char ** candidats);




#endif

