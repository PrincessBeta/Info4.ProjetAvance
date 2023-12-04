
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "liste.h"


List *list_create() {
	List *l = malloc(sizeof(List));
	Element *s = malloc(sizeof(Element));
	l->size = 0;
	l->sentinel = s;
	s->next = s;
	s->previous = s;
	
	return l;
}


List *list_push_back(List *l, void* v) {
	Element *e = malloc(sizeof(Element));
	e->value = v;
	e->next = l->sentinel;
	e->previous = l->sentinel->previous;
	l->sentinel->previous->next = e;
	l->sentinel->previous = e;
	l->size++;
	return l;
}

void list_delete(List **l) {
	List *l2 = *l;
	for(Element *e = l2->sentinel->next->next; e != l2->sentinel; e =e->next){
		free(e->previous);
	}
	free(l2->sentinel->previous);
	free(l2->sentinel);
	free(l2);
	l=NULL;
}

List *list_push_front(List *l, void* v) {
	Element *e = malloc(sizeof(Element));
	e->value = v;
	e->previous = l->sentinel;
	e->next = l->sentinel->next;
	l->sentinel->next->previous = e;
	l->sentinel->next = e;
	l->size++;
	return l;
}

void* list_front(List *l) {
	assert(!list_is_empty(l));
	return l->sentinel->next->value;
}

void* list_back(List *l) {
	assert(!list_is_empty(l));
	return l->sentinel->previous->value;
}

List *list_pop_front(List *l) {
	Element *e = l->sentinel->next;
	l->sentinel->next = e->next;
	e->next->previous = l->sentinel;

	l->size--;
	free(e);
	return l;
}

List *list_pop_back(List *l){
	Element *e = l->sentinel->previous;
	l->sentinel->previous = e->previous;
	e->previous->next = l->sentinel;
	l->size--;
	free(e);
	return l;
}

List *list_insert_at(List *l, int p, void* v) {
	Element *new = malloc(sizeof(Element));
	new->value = v;

	Element *e = l->sentinel;
	for (int i = 0; i <= p; i++) e = e->next;

	new->previous = e->previous;
	new->next = e;
	e->previous->next = new;
	e->previous = new;

	l->size ++;
	return l;
}

List *list_remove_at(List *l, int p) {
	Element *e = l->sentinel;

	for (int i = 0; i <= p; i++) e = e->next;

	e->next->previous = e->previous;
	e->previous->next = e->next;
	l->size--;
	free(e);
	return l;
}


void* list_at(List *l, int p) {
	Element *e = l->sentinel;
	for (int i = 0; i <= p; i++) e = e->next;
	return e->value;
}


bool list_is_empty(List *l) {
	return l->sentinel->next == l->sentinel;
}


int list_size(List *l) {
	return l->size;
}

bool list_in(List *l,void * e) {
	bool in = false;
	for (int i = 0;i<list_size(l) && !in;i++)
		in = list_at(l,i) == e;
	return in;
}

List * list_del_elt(List * l,void * e) {
	for (int i = 0;i<list_size(l);i++)
		if (list_at(l,i) == e) list_remove_at(l,i);
	return l;
}


List *list_map(List *l, SimpleFunctor f){

	for(Element *e = l->sentinel->next; e != l->sentinel; e =e->next){
		e -> value = f(e->value);
	}
	return l;
}


List *list_reduce(List *l, ReduceFunctor f, void *userData) {
	for(Element *e = l->sentinel->next; e != l->sentinel; e =e->next){
		f(e->value,userData);
	}
	return l;
}



