//
// Created by Romain SAMSON on 07/11/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Adverbe.h"

#ifndef MAIN_C_ADJECTIF_H
#define MAIN_C_ADJECTIF_H
//Struture pour l'arbre, la feuille et les noeuds de l'adjectif
typedef struct node_adjectif{
    struct node_adjectif *suite;
    char lettre;
    struct node_adjectif *autre;
    struct feuilleAdjectif *feuilleAdjectifPointeur;
}*nodeAdjectif;
struct feuilleAdjectif{
    char* femSG;
    char* femPL;
    char* masSG;
    char* masPL;
    char* invariableSG;
    char* invariablePL;
};
struct arbre_adjectif
{
    nodeAdjectif racine;
};
//prototypes des fonctions adjectifs
void freeNodeAdjectif(nodeAdjectif );
nodeAdjectif createNodeAdjetif(char );
void upArbreAdjectif(char* , char* , char* , struct arbre_adjectif* );
void rechercheAdjectif(nodeAdjectif ,int *);
void rechercheAccordAdjectif(nodeAdjectif ,int *, int*);
#endif //MAIN_C_ADJECTIF_H
