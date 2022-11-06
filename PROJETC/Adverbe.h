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
    int taille;
}*nodeAdverbe;
struct arbre_adverbe
{
    nodeAdverbe racine;
};

/*//Struture pour l'arbre, la feuille et les noeuds du nom
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
};*/

//Struture pour l'arbre, la feuille et les noeuds de l'adjectif
typedef struct node_adjectif{
    struct node_nom *suite;
    char lettre;
    struct node_nom *autre;
    struct feuilleNom *feuilleNomPointeur;
    int taille;
}*nodeAdjectif;
struct feuilleAdjectif{
    char* femSG;
    char* femPL;
    char* masSG;
    char* masPL;
    char* invariable;
};
struct arbre_adjectif
{
    nodeAdjectif racine;
};

struct arbre_adverbe createEmptyTree();
void extraireFichier(char* , char* , char* , char* );
void upArbreAdverbe(char* ,struct arbre_adverbe*);
nodeAdverbe createNodeAdv(char ,int);
char* createFeuilleAdv(char* ,int);
void rechercheAdv( nodeAdverbe);
int aleatoireAutre(int );
void freeNodeAdv(nodeAdverbe );
/*void rechercheNom(nodeNom);
void freeNodeNom(nodeNom );
nodeNom createNodeNom(char );
void upArbreNom(char*, char*, char*, struct arbre_nom*);*/
#endif //PROJETC_NODE_H
