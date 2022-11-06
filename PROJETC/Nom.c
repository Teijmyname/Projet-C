//
// Created by Romain SAMSON on 06/11/2022.
//

#include "Nom.h"
void freeNodeNom(nodeNom node) {
    if (node->suite)
        freeNodeNom(node->suite);
    if (node->autre)
        freeNodeNom(node->autre);
    if (node->feuilleNomPointeur)
        free(node->feuilleNomPointeur);
    free(node);
}
nodeNom createNodeNom(char theLettre)
{
    nodeNom nouv;


    nouv = (nodeNom)malloc(sizeof(struct node_nom));
    nouv->lettre = theLettre;
    nouv->suite = nouv->autre = NULL;
    nouv->feuilleNomPointeur = malloc(sizeof (struct feuilleNom));
    nouv->feuilleNomPointeur->femPL = nouv->feuilleNomPointeur->femSG  = nouv->feuilleNomPointeur->masPL = nouv->feuilleNomPointeur->masSG = nouv->feuilleNomPointeur->invariable = NULL;
    printf("creation du noeud %c \n" ,theLettre);

    return nouv;
}
void upArbreNom(char* flechie, char* base, char* info, struct arbre_nom* arbre){
    int i;
    nodeNom node;
    int taille = 0;
    int tailleFlechie =0;
    for(i =0;flechie[i] != '\0'; i++){
        tailleFlechie++;
    }
    for (i = 0; base[i] != '\0'; i++) {
        taille++;
    }
    //on pointe node sur la première lettre du mot que nous voulons implémenter dans l'arbre
    if (!arbre->racine) {
        arbre->racine = createNodeNom(base[0]);
    }
    //nous allons implémenter les autres jusqu'à la dernière
    // apres chaque mot retour en haut de l'arbre
    nodeNom curseur;
    curseur = arbre->racine;
    for(i=0;i<taille-1;i++) {
        while (curseur->lettre != base[i] && curseur->autre != NULL) {
            curseur = curseur->autre;
        }
        if (curseur->lettre != base[i]) {
            node = createNodeNom(base[i]);
            printf("stockage dans le dernier suivant de la lettre %c\n", node->lettre);
            curseur->autre = node;
            curseur = curseur->autre;
        }
        if(i != taille-1) {
            if (!curseur->suite) {
                node = createNodeNom(base[i+1]);
                curseur->suite = node;
            }
            curseur = curseur->suite;
        }
    }
    //creation de la feuille associée
    if(info[4] == 'M' && info[8] == 'S'){
        curseur->feuilleNomPointeur->masSG = malloc(tailleFlechie * sizeof(char));
        strcpy(curseur->feuilleNomPointeur->masSG,  flechie);
        printf("LA FEUILLE DU NOM MAS SG EST = %s\n",curseur->feuilleNomPointeur->masSG);
        return;
    }
    if(info[4] == 'F'&& info[8] == 'S'){
        curseur->feuilleNomPointeur->femSG = malloc(tailleFlechie * sizeof(char));
        strcpy(curseur->feuilleNomPointeur->femSG,  flechie);
        printf("LA FEUILLE DU NOM feminim SG EST = %s\n",curseur->feuilleNomPointeur->femSG);
        return;
    }
    if(info[4] == 'M'&& info[8] == 'P') {
        curseur->feuilleNomPointeur->masPL = malloc(tailleFlechie * sizeof(char));
        strcpy(curseur->feuilleNomPointeur->masPL, flechie);
        printf("LA FEUILLE DU NOM MASCULIN PL EST = %s\n", curseur->feuilleNomPointeur->masPL);
        return;
    }
    if(info[4] == 'F'&& info[8] == 'P') {
        curseur->feuilleNomPointeur->femPL = malloc(tailleFlechie * sizeof(char));
        strcpy(curseur->feuilleNomPointeur->femPL, flechie);
        printf("LA FEUILLE DU NOM feminim PL EST = %s\n", curseur->feuilleNomPointeur->femPL);
        return;
    }
    else{
        curseur->feuilleNomPointeur->invariable = malloc(tailleFlechie * sizeof(char));
        strcpy(curseur->feuilleNomPointeur->invariable, flechie);
        printf("LA FEUILLE DU NOM  EST INVARIABLE = %s\n", curseur->feuilleNomPointeur->invariable);
        return;
    }
}
void rechercheNom(nodeNom node){
    int nbAutre =0;
    nodeNom curseur = node;
    while(curseur->autre){
        nbAutre ++;
        curseur=curseur->autre;
    }
    //printf("nbAutre = %d\n",nbAutre);
    if(nbAutre != 0) {
        int i = 0;
        int rd = aleatoireAutre(nbAutre+1);
        while (i != rd) {
            i++;
            node = node->autre;
        }
    }
    //printf("%c\n",node->lettre);
    if(node->feuilleNomPointeur->invariable!=NULL || node->feuilleNomPointeur->masSG!=NULL || node->feuilleNomPointeur->masPL!=NULL || node->feuilleNomPointeur->femSG!=NULL ||node->feuilleNomPointeur->femPL!=NULL){
        if(!node->suite) {
            //printf("%s", node->feuilleAdverbe);
            if(node->feuilleNomPointeur->invariable!=NULL) {
                printf("%s", node->feuilleNomPointeur->invariable);
//                accord[0] = 'I';
                return;
            }
            else{
                int rd = aleatoireAutre(4);
                if(rd == 0 && node->feuilleNomPointeur->masSG!=NULL) {
                    printf("%s", node->feuilleNomPointeur->masSG);
                    //accord[0] = 'M';
                    //accord[1] = 'S';
                    return;
                }
                if(rd == 1 && node->feuilleNomPointeur->masPL!=NULL) {
                    printf("%s", node->feuilleNomPointeur->masPL);
                    //accord[0] = 'M';
                    //accord[1] = 'P';
                    return;
                }
                if(rd == 2 && node->feuilleNomPointeur->femSG !=NULL ){
                    printf("%s", node->feuilleNomPointeur->femSG);
                    //accord[0] = 'F';
                    //accord[1] = 'S';
                    return;
                }
                if(rd == 3 && node->feuilleNomPointeur->femPL !=NULL ) {
                    printf("%s", node->feuilleNomPointeur->femPL);
                    //accord[0] = 'F';
                    //accord[1] = 'L';
                    return;
                }
                else
                    rechercheNom(node);
            }
        }
        else{

            int continuer = aleatoireAutre(2);
            //printf("random de feuiile AVECCCCC suite = %d",continuer);
            if(continuer == 0){
                if(node->feuilleNomPointeur->invariable!=NULL) {
                    printf("%s", node->feuilleNomPointeur->invariable);
                    //accord[0] = 'I';
                    return;
                }
                else {
                    int rd = aleatoireAutre(4);
                    if (rd == 0 && node->feuilleNomPointeur->masSG != NULL) {
                        printf("%s", node->feuilleNomPointeur->masSG);
                        //accord[0] = 'M';
                        //accord[1] = 'S';
                        return;
                    }
                    if (rd == 1 && node->feuilleNomPointeur->masPL != NULL) {
                        printf("%s", node->feuilleNomPointeur->masPL);
                        //accord[0] = 'M';
                        //accord[1] = 'P';
                        return;
                    }
                    if (rd == 2 && node->feuilleNomPointeur->femSG != NULL) {
                        printf("%s", node->feuilleNomPointeur->femSG);
                        //accord[0] = 'F';
                        //accord[1] = 'S';
                        return;
                    }
                    if (rd == 3 && node->feuilleNomPointeur->femPL != NULL) {
                        printf("%s", node->feuilleNomPointeur->femPL);
                        //accord[0] = 'F';
                        //accord[1] = 'L';
                        return;
                    }
                    else
                        rechercheNom(node);
                }
            }
            else{
                node = node->suite;
                rechercheNom(node);
            }
        }
    }
    else{
        if(!node->suite)
            printf("erreur dans la recherche pas de suite");
        else{
            node = node->suite;
            rechercheNom(node);
        }
    }
    return;

}