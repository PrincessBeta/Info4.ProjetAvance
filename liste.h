#ifndef LISTE_H
#define LISTE_H

#include "liste_element.h"
#include <stdbool.h>

/// \typedef Liste
/// \brief Liste chainée avec sentinelle
/// \author Yael Bourguignon
/// \date 10/10/2023
typedef struct _List {
    int size;
    Element* sentinel;
} List;

/// @brief types utilisés pour le map et le reduce
typedef void*(*SimpleFunctor)(void*);
typedef void*(*ReduceFunctor)(void*, void *);


/// \brief créé une liste vide
/// \author Yael Bourguignon
/// \date 10/10/2023
List* list_create();

void list_delete(List** l);

/// \brief renvoie la longueur de la liste l
/// \author Yael Bourguignon
/// \date 10/10/2023
int list_size(List *l);

bool list_is_empty(List *l);

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

/// \brief verifie si l'element e est dans la liste
/// \author Raphaël Rumin
/// \date 02/12/2023
bool list_in(List *l,void * e);

/// \brief supprime toutes les occurences d'un element dans la liste
/// \author Raphaël Rumin
/// \date 02/12/2023
List * list_del_elt(List * l,void * e);

List* list_insert_at(List *l, int p, void* v);

List* list_remove_at(List *l, int p);

List *list_map(List *l, SimpleFunctor f);

List *list_reduce(List *l, ReduceFunctor f, void* userData);

#endif
