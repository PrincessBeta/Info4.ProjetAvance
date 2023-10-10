#ifndef LISTE_H
#define LISTE_H

#include "liste_element.h"

/// \typedef Liste
/// \brief Liste
/// \author Yael Bourguignon
/// \date 10/10/2023
typedef struct _List List;

int list_size(List *l);

List* list_create();

void* list_front(List *l);

void* list_back(List *l);

List* list_push_front(List *l, void* value);

List* list_push_back(List *l, void* value);

List* list_pop_front(List *l);

List* list_pop_back(List *l);

void* list_at(List *l, int n);

#endif