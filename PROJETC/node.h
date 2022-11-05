//
// Created by Teij Jayantilal on 24/10/2022.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef PROJETC_NODE_H
#define PROJETC_NODE_H
//Structure de tableaux pour les nœuds
//#define ALPHABET_SIZE 26
//structure pour les noeuds d'arbres binaires

typedef struct node_adverbe
{
	struct node_adverbe *suite;
	char lettre;
	struct node_adverbe *autre;
    char* feuilleAdverbe;
    int taille;
}*nodeAdverbe;
//structure de l'arbre(racine)
typedef struct arbre_adverbe
{
    nodeAdverbe racine;
}*arbreAdv;
struct arbre_adverbe createEmptyTree();
void extraireFichier(char* , char* , char* , char* );
void upArbreAdverbe(char* ,struct arbre_adverbe*);
nodeAdverbe createNodeAdv(char ,int);
nodeAdverbe createLastNodeAdv(char ,int);
char* createFeuilleAdv(char* ,int);
void rechercheAdv( nodeAdverbe);
int aleatoireAutre(int NbAutre);
void freeNodeAdv(nodeAdverbe node);
#endif //PROJETC_NODE_H
