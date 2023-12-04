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

#endif

