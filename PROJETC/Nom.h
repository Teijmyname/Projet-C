//
// Created by Romain SAMSON on 06/11/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Adverbe.h"
#ifndef MAIN_C_NOM_H
#define MAIN_C_NOM_H
//Struture pour l'arbre, la feuille et les noeuds du nom
typedef struct node_nom{
    struct node_nom *suite;
    char lettre;
    struct node_nom *autre;
    struct feuilleNom *feuilleNomPointeur;
}*nodeNom;
struct feuilleNom{
    char* femSG;
    char* femPL;
    char* masSG;
    char* masPL;
    char* invariableSG;
    char* invariablePL;
};
struct arbre_nom
{
    nodeNom racine;
};
//prototypes des fonctions de nom
void rechercheNom(nodeNom, int*);
void rechercheAccordNom(nodeNom ,int *, int* );
void freeNodeNom(nodeNom );
nodeNom createNodeNom(char );
void upArbreNom(char*, char*, char*, struct arbre_nom*);

void rechercheBaseNom(nodeNom);
#endif //MAIN_C_NOM_H
