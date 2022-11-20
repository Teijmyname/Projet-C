//
// Created by Romain SAMSON on 07/11/2022.
//
#include "Adjectif.h"
//fonction qui permet de liberer l'espace alloué
void freeNodeAdjectif(nodeAdjectif node) {
    if (node->suite)
        freeNodeAdjectif(node->suite);
    if (node->autre)
        freeNodeAdjectif(node->autre);
    if (node->feuilleAdjectifPointeur->invariableSG)
        free(node->feuilleAdjectifPointeur->invariableSG);
    if (node->feuilleAdjectifPointeur->invariablePL)
        free(node->feuilleAdjectifPointeur->invariablePL);
    if (node->feuilleAdjectifPointeur->masSG)
        free(node->feuilleAdjectifPointeur->masSG);
    if(node->feuilleAdjectifPointeur->masPL)
        free(node->feuilleAdjectifPointeur->masPL);
    if(node->feuilleAdjectifPointeur->femSG)
        free(node->feuilleAdjectifPointeur->femSG);
    if(node->feuilleAdjectifPointeur->femPL)
        free(node->feuilleAdjectifPointeur->femPL);
    free(node->feuilleAdjectifPointeur);
    free(node);
    return;
}

//fonction qui va permettre de créer chaque noeud
nodeAdjectif createNodeAdjetif(char theLettre)
{
    nodeAdjectif nouv;
    nouv = (nodeAdjectif)malloc(sizeof(struct node_adjectif));
    nouv->lettre = theLettre;
    nouv->suite = nouv->autre = NULL;
    nouv->feuilleAdjectifPointeur = malloc(sizeof (struct feuilleAdjectif));
    nouv->feuilleAdjectifPointeur->femPL = nouv->feuilleAdjectifPointeur->femSG  = nouv->feuilleAdjectifPointeur->masPL = nouv->feuilleAdjectifPointeur->masSG = NULL;
    nouv->feuilleAdjectifPointeur->invariableSG = nouv->feuilleAdjectifPointeur->invariablePL = NULL;
    return nouv;
}

//permet d'incrémenter chaque nouveau adjectif dans l'arbre des adjectifs
void upArbreAdjectif(char* flechie, char* base, char* info, struct arbre_adjectif* arbre){
    int i;
    nodeAdjectif node;
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
        arbre->racine = createNodeAdjetif(base[0]);
    }
    //nous allons implémenter les autres jusqu'à la dernière
    // apres chaque mot retour en haut de l'arbre
    nodeAdjectif curseur;
    curseur = arbre->racine;
    for(i=0;i<taille-1;i++) {
        while (curseur->lettre != base[i] && curseur->autre != NULL) {
            curseur = curseur->autre;
        }
        if (curseur->lettre != base[i]) {
            node = createNodeAdjetif(base[i]);
            curseur->autre = node;
            curseur = curseur->autre;
        }
        if(i != taille-1) {
            if (!curseur->suite) {
                node = createNodeAdjetif(base[i+1]);
                curseur->suite = node;
            }
            curseur = curseur->suite;
        }
    }
    //creation de la feuille associée
    if(info[4] == 'M' && info[8] == 'S'){
        curseur->feuilleAdjectifPointeur->masSG = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleAdjectifPointeur->masSG,  flechie, tailleFlechie);
        return;
    }
    if(info[4] == 'F'&& info[8] == 'S'){
        curseur->feuilleAdjectifPointeur->femSG = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleAdjectifPointeur->femSG,  flechie, tailleFlechie);
        return;
    }
    if(info[4] == 'M'&& info[8] == 'P') {
        curseur->feuilleAdjectifPointeur->masPL = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleAdjectifPointeur->masPL, flechie, tailleFlechie);
        return;
    }
    if(info[4] == 'F'&& info[8] == 'P') {
        curseur->feuilleAdjectifPointeur->femPL = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleAdjectifPointeur->femPL, flechie, tailleFlechie);
        return;
    }
    if (info[4] == 'I' && info[11] == 'S'){
        curseur->feuilleAdjectifPointeur->invariableSG = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleAdjectifPointeur->invariableSG, flechie, tailleFlechie);
        return;
    }
    if (info[4] == 'I' && info[11] == 'P'){
        curseur->feuilleAdjectifPointeur->invariablePL = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleAdjectifPointeur->invariablePL, flechie, tailleFlechie);
        return;
    }
    return;
}

//recherche aléatoirement une forme de base d'un adjectif
void rechercheBaseAdj(nodeAdjectif node) {
    int nbAutre = 0;
    nodeAdjectif curseur = node;
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
    if (node->feuilleAdjectifPointeur->invariableSG != NULL || node->feuilleAdjectifPointeur->invariablePL != NULL ||
        node->feuilleAdjectifPointeur->masSG != NULL || node->feuilleAdjectifPointeur->masPL != NULL ||
        node->feuilleAdjectifPointeur->femSG != NULL || node->feuilleAdjectifPointeur->femPL != NULL) {
        if (!node->suite) {
            return;

        }

        else {
            int continuer = aleatoireAutre(2);
            //si continuer = 0 alors on s'arrete au noeud où il y a une forme conjugué sinon on continue
            if (continuer == 0) {
                return;
            } else {
                node = node->suite;
                rechercheBaseAdj(node);
            }
        }
    }
    else{
        if(!node->suite)
            return;
        else{
            node = node->suite;
            rechercheBaseAdj(node);
        }
    }
    return;
}
// recherche Adjectif avec l'accord du nom
void rechercheAccordAdjectif(nodeAdjectif node,int *accord, int* correct){
    int nbAutre =0;
    nodeAdjectif curseur = node;
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
    if(node->feuilleAdjectifPointeur->invariableSG!=NULL || node->feuilleAdjectifPointeur->invariablePL!=NULL || node->feuilleAdjectifPointeur->masSG!=NULL || node->feuilleAdjectifPointeur->masPL!=NULL || node->feuilleAdjectifPointeur->femSG!=NULL ||node->feuilleAdjectifPointeur->femPL!=NULL){
        if(!node->suite) {
            if(node->feuilleAdjectifPointeur->invariableSG!=NULL && *accord == 0)
            //accord à 0 correspond à l'accord invariable singulier
            {
                printf("%s ", node->feuilleAdjectifPointeur->invariableSG);
                *correct = 1;
                return;
            }
            if(node->feuilleAdjectifPointeur->invariablePL!=NULL && *accord == 1) {
                //accord à 1 correspond à l'accord invariable pluriel
                printf("%s ", node->feuilleAdjectifPointeur->invariablePL);
                *correct = 1;
                return;
            }
            if ((*accord == 2 || *accord == 0) && node->feuilleAdjectifPointeur->masSG != NULL) {
                //accord à 2 correspond à l'accord masculin pluriel
                printf("%s ", node->feuilleAdjectifPointeur->masSG);
                *accord = 2;
                *correct = 1;
                return;
            }
            if ((*accord == 3 || *accord==1)&& node->feuilleAdjectifPointeur->masPL != NULL) {
                printf("%s ", node->feuilleAdjectifPointeur->masPL);
                *accord = 3;
                *correct = 1;
                return;
            }
            if ((*accord == 4 || *accord == 0) && node->feuilleAdjectifPointeur->femSG != NULL) {
                printf("%s ", node->feuilleAdjectifPointeur->femSG);
                *accord = 4;
                *correct = 1;
                return;
            }
            if ((*accord == 5 || *accord==1)&& node->feuilleAdjectifPointeur->femPL != NULL) {
                printf("%s ", node->feuilleAdjectifPointeur->femPL);
                *accord = 4;
                *correct = 1;
                return;
            }
        }
        else{

            int continuer = aleatoireAutre(2);
            if(continuer == 0){
                //si continuer = 0 alors on s'arrete au noeud où il y a une forme conjugué sinon on continue
                if(node->feuilleAdjectifPointeur->invariableSG!=NULL && *accord == 0) {
                    printf("%s ", node->feuilleAdjectifPointeur->invariableSG);
                    *correct = 1;
                    return;
                }
                if(node->feuilleAdjectifPointeur->invariablePL!=NULL && *accord == 1) {
                    printf("%s ", node->feuilleAdjectifPointeur->invariablePL);
                    *correct = 1;
                    return;
                }
                if ((*accord == 2 || *accord == 0) && node->feuilleAdjectifPointeur->masSG != NULL) {
                    printf("%s ", node->feuilleAdjectifPointeur->masSG);
                    *accord = 2;
                    *correct = 1;
                    return;
                }
                if ((*accord == 3 || *accord==1)&& node->feuilleAdjectifPointeur->masPL != NULL) {
                    printf("%s ", node->feuilleAdjectifPointeur->masPL);
                    *accord = 3;
                    *correct = 1;
                    return;
                }
                if ((*accord == 4 || *accord == 0) && node->feuilleAdjectifPointeur->femSG != NULL) {
                    printf("%s ", node->feuilleAdjectifPointeur->femSG);
                    *accord = 4;
                    *correct = 1;
                    return;
                }
                if ((*accord == 5 || *accord==1)&& node->feuilleAdjectifPointeur->femPL != NULL) {
                    printf("%s ", node->feuilleAdjectifPointeur->femPL);
                    *accord = 5;
                    *correct = 1;
                    return;
                }
            }
            else{
                node = node->suite;
                rechercheAccordAdjectif(node, accord, correct);
            }
        }
    }
    else{
        if(!node->suite)
            return;
        else{
            node = node->suite;
            rechercheAccordAdjectif(node, accord, correct);
        }
    }
    return;
}
