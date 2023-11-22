#include "liste.h"

int main(int argc, char const *argv[])
{
    List* l;
    l = list_create();
    int i = 146;
    list_push_back(l,i);
    return 0;
}
