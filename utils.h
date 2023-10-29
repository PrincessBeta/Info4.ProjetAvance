#ifndef UTILS_H
#define UTILS_H

#include "liste.h"

#define VOTE_CONDORCET 1 
#define VOTE_JUGEMENT 2


/// \brief returns a list of a person's votes
/// \author Yael Bourguignon
/// \date 10/10/2023
/// \param surname the person's surname 
/// \param name the person's name
/// \param num_etu the person's student number
/// \return the list of the person's votes
List getVotesPersonne(char* surname, char* name, char* num_etu,int voteType);

// void upper(char* string){

#endif