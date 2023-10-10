#include "liste_element.h"
#include <stdlib.h>

Element* next(Element* e) {
    return e->next;
}

void* value(Element* e) {
    return e->value;
}
