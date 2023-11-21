#include "liste.h"
#include "stdlib.h"
#include <stdio.h>


int list_size(List *l) {
    return l->size;
}

List* list_create(){
    List* l = malloc(sizeof(List));
    Element* sentinel = malloc(sizeof(Element));
    l->size = 0;
    l->sentinel = sentinel;
    return l;
}

void* list_front(List *l){
    return l->sentinel->next;
}

void* list_back(List *l){
    return l->sentinel->prev;
}

List* list_push_front(List *l, void* value){
    Element* e = malloc(sizeof(Element));
    e->value = value;
    e->prev = l->sentinel;
    e->next = l->sentinel->next;
    l->sentinel->next->prev = e;
    l->sentinel->next = e;
    l->size++;
    return l;
}

List* list_push_back(List *l, void* value){
    Element* e = malloc(sizeof(Element));
    e->value = value;
    e->next = l->sentinel;
    e->prev = l->sentinel->prev;
    l->sentinel->prev->next = e;
    l->sentinel->prev = e;
    l->size++;
    return l;
}

List* list_pop_front(List *l){
    Element *e = l->sentinel->next;
	l->sentinel->next = e->next;
	e->next->prev = l->sentinel;

	l->size--;
	free(e);
	return l;
}

List* list_pop_back(List *l){
    Element *e = l->sentinel->prev;
	l->sentinel->prev = e->prev;
	e->prev->next = l->sentinel;
	l->size--;
	free(e);
	return l;
}

void* list_at(List *l, int n) {
    Element *e = l->sentinel;
    for (int i = 0; i < n; i++)
    {
        e = e->next;
    }
    return e->value;
    
}