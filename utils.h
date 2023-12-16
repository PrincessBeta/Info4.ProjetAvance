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

/// \brief returns a table of all the vote
/// \author Yousra Arroui
/// \date 10/10/2023
int **createVoteTable(Matrix *csvMatrix);

/// \brief returns a table of all the vote
/// \author Yousra Arroui
/// \date 10/10/2023
void printTable(int **table, int numRows, int numCols, const char *rowLabel, const char *colLabel);

#endif
