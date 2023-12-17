#ifndef CONDORCET_SCHULZE_H
#define CONDORCET_SCHULZE_H

#include "liste.h"
#include "graphe.h"
#include "lecture_csv.h"

/// \brief Retourne le ou les gagnants par la méthode de Schulze, sous forme de Liste. La taille de la liste est le nombre de gagnant.
/// \author Raphaël Rumin
/// \date 09/12/2023
List * condorcet_schulze(Matrix * m,char ** candidats);

#endif

