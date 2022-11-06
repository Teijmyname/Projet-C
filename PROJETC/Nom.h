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
    int taille;
}*nodeNom;
struct feuilleNom{
    char* femSG;
    char* femPL;
    char* masSG;
    char* masPL;
    char* invariable;
};
struct arbre_nom
{
    nodeNom racine;
};
void rechercheNom(nodeNom);
void freeNodeNom(nodeNom );
nodeNom createNodeNom(char );
void upArbreNom(char*, char*, char*, struct arbre_nom*);
#endif //MAIN_C_NOM_H
