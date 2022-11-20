//
// Created by Romain SAMSON on 10/11/2022.
//

#include "Verbe.h"
//fonction qui permet de liberer l'espace alloué
void freeNodeVerbe(nodeVerbe node){
    if (node->suite)
        freeNodeVerbe(node->suite);
    if (node->autre)
        freeNodeVerbe(node->autre);
    if (node->conjugaison->SG)
        free(node->conjugaison->SG);
    if (node->conjugaison->PL)
        free(node->conjugaison->PL);
    free(node->conjugaison);
    free(node);
    return;

}
//fonction qui va permettre de créer chaque noeud
nodeVerbe createNodeVerbe(char theLettre){
    nodeVerbe nouv;
    nouv = (nodeVerbe)malloc(sizeof(struct node_verbe));
    nouv->lettre = theLettre;
    nouv->suite = nouv->autre = NULL;
    nouv->conjugaison = malloc(sizeof (struct feuilleVerbe));
    nouv->conjugaison->PL = nouv->conjugaison->SG = NULL;
    return nouv;
}
//permet d'incrémenter chaque nouveau verbe dans l'arbre des verbes
void upArbreVerbe(char* flechie, char* base, char* info, struct arbre_verbe* arbre){
    int i;
    nodeVerbe node;
    int taille = 0;
    int tailleFlechie =0;
    for(i =0;flechie[i] != '\0'; i++){
        tailleFlechie++;
    }
    tailleFlechie = tailleFlechie+1;
    for (i = 0; base[i] != '\0'; i++) {
        taille++;
    }
    //on pointe node sur la première lettre du mot que nous voulons implémenter dans l'arbre
    if (!arbre->racine) {
        arbre->racine = createNodeVerbe(base[0]);
    }
    //nous allons implémenter les autres jusqu'à la dernière
    // apres chaque mot retour en haut de l'arbre
    nodeVerbe curseur;
    curseur = arbre->racine;
    for(i=0;i<taille-1;i++) {
        while (curseur->lettre != base[i] && curseur->autre != NULL) {
            curseur = curseur->autre;
        }
        if (curseur->lettre != base[i]) {
            node = createNodeVerbe(base[i]);
            curseur->autre = node;
            curseur = curseur->autre;
        }
        if(i != taille-1) {
            if (!curseur->suite) {
                node = createNodeVerbe(base[i+1]);
                curseur->suite = node;
            }
            curseur = curseur->suite;
        }
    }
    //creation de la feuille associée
    if(info[9] == 'S'){
        curseur->conjugaison->SG = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->conjugaison->SG,  flechie, tailleFlechie);
        return;
    }
    if(info[9] == 'P'){
        curseur->conjugaison->PL = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->conjugaison->PL,  flechie, tailleFlechie);
        return;
    }
    return;
}

void rechercheBaseVerbe(nodeVerbe node) {
    int nbAutre = 0;
    nodeVerbe curseur = node;
    while (curseur->autre) {
        nbAutre++;
        curseur = curseur->autre;
    }
    if (nbAutre != 0) {
        int i = 0;
        int rd = aleatoireAutre(nbAutre + 1);
        while (i != rd) {
            i++;
            node = node->autre;
        }
    }
    printf("%c",node->lettre);
    if(node->conjugaison->SG!=NULL || node->conjugaison->PL !=NULL) {
        if (!node->suite) {
            return;
        }
        else {
            int continuer = aleatoireAutre(2);
            //si continuer = 0 alors on s'arrete au noeud où il y a une forme conjugué sinon on continue
            if (continuer == 0)
                return;
            else {
                node = node->suite;
                rechercheBaseVerbe(node);
            }
        }
    }
    else{
        if(!node->suite)
            return;
        else{
            node = node->suite;
            rechercheBaseVerbe(node);
        }
    }
    return;
}
//permet de rechercher dans l'arbre verbe un verbe aléatoirement avec l'accord de la phrase
void rechercheAccordVerbe(nodeVerbe node,int *accord, int *correct){
    int nbAutre =0;
    nodeVerbe curseur = node;
    while(curseur->autre){
        nbAutre ++;
        curseur=curseur->autre;
    }
    if(nbAutre != 0) {
        int i = 0;
        int rd = aleatoireAutre(nbAutre);
        while (i != rd) {
            i++;
            node = node->autre;
        }
    }
    if(node->conjugaison->SG!=NULL || node->conjugaison->PL !=NULL) {
        if (!node->suite) {
            if (node->conjugaison->SG != NULL && (*accord == 0 || *accord == 2 || *accord == 4)) {
                printf("%s ", node->conjugaison->SG);
                *correct=1;
                return;
            }
            if (node->conjugaison->PL != NULL && (*accord == 1 || *accord == 3 || *accord == 5)) {
                printf("%s ", node->conjugaison->PL);
                *correct=1;
                return;
            }
        }
        else {
            int continuer = aleatoireAutre(2);
            //si continuer = 0 alors on s'arrete au noeud où il y a une forme conjugué sinon on continue
            if (continuer == 0) {
                if (node->conjugaison->SG != NULL && (*accord == 0 || *accord == 2 || *accord == 4)) {
                    printf("%s ", node->conjugaison->SG);
                    *correct=1;
                    return;
                }

                if (node->conjugaison->PL != NULL && (*accord == 1 || *accord == 3 || *accord == 5)) {
                    printf("%s ", node->conjugaison->PL);
                    *correct=1;
                    return;
                }
            }
            else {
                node = node->suite;
                rechercheAccordVerbe(node, accord, correct);
            }
        }
    }
    else{
        if(!node->suite)
            return;
        else{
            node = node->suite;
            rechercheAccordVerbe(node, accord, correct);
        }
    }
    return;
}