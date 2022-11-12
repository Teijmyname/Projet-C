//
// Created by Romain SAMSON on 10/11/2022.
//

#ifndef MAIN_C_VERBE_H
#define MAIN_C_VERBE_H
#include "Adverbe.h"
//Struture pour l'arbre, la feuille et les noeuds du verbe
typedef struct node_verbe {
    struct node_verbe *suite;
    char lettre;
    struct node_verbe *autre;
    struct feuilleVerbe *conjugaison;
}*nodeVerbe;
struct feuilleVerbe{
    char* SG;
    char* PL;
};
struct arbre_verbe
{
    nodeVerbe racine;
};
//prototypes des fonctions de verbe
void freeNodeVerbe(nodeVerbe);
nodeVerbe createNodeVerbe(char);
void upArbreVerbe(char* , char* , char* , struct arbre_verbe* );
void rechercheAccordVerbe(nodeVerbe ,int*, int*);
#endif //MAIN_C_VERBE_H
