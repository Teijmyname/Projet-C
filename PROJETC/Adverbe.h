//
// Created by Teij Jayantilal on 24/10/2022.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef PROJETC_NODE_H
#define PROJETC_NODE_H
//structure pour les noeuds de l'arbre adverbe
typedef struct node_adverbe
{
	struct node_adverbe *suite;
	char lettre;
	struct node_adverbe *autre;
    char* feuilleAdverbe;
}*nodeAdverbe;
struct arbre_adverbe
{
    nodeAdverbe racine;
};

struct arbre_adverbe createEmptyTree();
void extraireFichier(char* , char* , char* , char* );
void upArbreAdverbe(char* ,struct arbre_adverbe*);
nodeAdverbe createNodeAdv(char ,int);
char* createFeuilleAdv(char* ,int);
void rechercheAdv( nodeAdverbe);
int aleatoireAutre(int );
void freeNodeAdv(nodeAdverbe );
#endif //PROJETC_NODE_H
