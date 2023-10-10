#ifndef LISTE_ELEMENT_H
#define LISTE_ELEMENT_H

/// \typedef
/// \brief Element d'une liste
/// \author Yael Bourguignon
/// \date 10/10/2023
typedef struct _Element
{
    void* value;
    struct _Element* next;
    struct _Element* prev;
} Element;

/// \brief renvoie l'element suivant e
/// \author Yael Bourguignon
/// \date 10/10/2023
Element* next(Element* e); 
/// \param[in] Element l'element dont on cherche le successeur
/// \return le successeur de e

/// \brief renvoie l'element précédant e
/// \author Yael Bourguignon
/// \date 10/10/2023
Element* previous(Element* e); 
/// \param[in] Element l'element dont on cherche le predecesseur
/// \return le successeur de e

/// \brief renvoie la valeur contenue dans e en tant que pointeur
/// \author Yael Bourguignon
/// \date 10/10/2023
void* value(Element* e);
/// \param[in] Element l'element dont on cherche la valeur
/// \return le pointeur contenu dans e


#endif