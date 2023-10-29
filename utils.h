#ifndef UTILS_H
#define UTILS_H
#define MAX_NAME_SIZE 100

/// \brief returns a list of a person's votes
/// \author Yael Bourguignon
/// \date 10/10/2023
/// \param surname the person's surname 
/// \param name the person's name
/// \param num_etu the person's student number
/// \return the list of the person's votes
void getVotes(char* surname, char* name, char* num_etu,const char* voteType,char* votes);

// void upper(char* string){

#endif