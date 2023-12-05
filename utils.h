#ifndef UTILS_H
#define UTILS_H
#define MAX_NAME_SIZE 100
#include "lecture_csv.h"

/// \brief returns a list of a person's votes
/// \author Yael Bourguignon
/// \date 10/10/2023
/// \param surname the person's surname 
/// \param name the person's name
/// \param num_etu the person's student number
/// \return the list of the person's votes
void getVotes(char* surname, char* name, char* num_etu,const char* voteType,char* votes);

// void upper(char* string){


/// \brief Convertit un int en string.
/// \author Raphaël Rumin
/// \date 04/12/2023
char * itoa(int x);

/// \brief Renvoie une matrice sans les l premières lignes et c premières colonnes de la matrice en paramètre.
/// \author Raphaël Rumin
/// \date 04/12/2023
Matrix * trim_matrix(Matrix * m,int l,int c);

/// \brief Renvoie une matrice de taille l*c remplie de 0.
/// \author Raphaël Rumin
/// \date 04/12/2023
Matrix * init_matrice_zero(int l,int c);

/// \brief Renvoie le tableau des candidats à partir d'un tableau sous la forme de la première ligne d'un vote moodle.
/// \author Raphaël Rumin
/// \date 05/12/2023
char ** liste_candidat_moodle(char ** tab,int n);

#endif
