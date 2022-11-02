//
// Created by Teij Jayantilal on 24/10/2022.
#include <stdio.h>
#include <stdlib.h>
#include <corecrt.h>
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
    struct node_adverbe* racine;
}*arbreAdv;
void MemoriserUneLigne( char*, char*);
int LongueurFichier( char * );
void extraireFichier(char* , char* , char* , char* );
void upArbreAdverbe(char* );
nodeAdverbe createNodeAdv(char );
#endif //PROJETC_NODE_H
