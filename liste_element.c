#include "liste_element.h"
#include <stdlib.h>

Element* next(Element* e) {
    return e->next;
}

Element* previous(Element* e){
    return e->previous;
}

int value(Element* e) {
    return e->value;
}
