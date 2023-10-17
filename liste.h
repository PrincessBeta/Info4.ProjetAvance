#ifndef LISTE_H
#define LISTE_H

#include "liste_element.h"

/// \typedef Liste
/// \brief Liste
/// \author Yael Bourguignon
/// \date 10/10/2023
typedef struct _List List;

/// \brief renvoie la longueur de la liste l
/// \author Yael Bourguignon
/// \date 10/10/2023
int list_size(List *l);

/// \brief créé une liste vide
/// \author Yael Bourguignon
/// \date 10/10/2023
List* list_create();

/// \brief renvoie le pointeur en tête de liste
/// \author Yael Bourguignon
/// \date 10/10/2023
void* list_front(List *l);

/// \brief renvoie le pointeur en queue de liste
/// \author Yael Bourguignon
/// \date 10/10/2023
void* list_back(List *l);

/// \brief ajoute le pointeur value en tête de la liste l
/// \author Yael Bourguignon
/// \date 10/10/2023
List* list_push_front(List *l, void* value);

/// \brief ajoute le pointeur value en queue de la liste l
/// \author Yael Bourguignon
/// \date 10/10/2023
List* list_push_back(List *l, void* value);

/// \brief enleve l'element en tête de la liste l
/// \author Yael Bourguignon
/// \date 10/10/2023
List* list_pop_front(List *l);

/// \brief enleve l'element en queue de la liste l
/// \author Yael Bourguignon
/// \date 10/10/2023
List* list_pop_back(List *l);

/// \brief renvoie le n-eme element de la liste l
/// \author Yael Bourguignon
/// \date 10/10/2023
void* list_at(List *l, int n);

#endif