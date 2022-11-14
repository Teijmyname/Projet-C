//
// Created by Romain SAMSON on 06/11/2022.
//

#include "Nom.h"
// permet de libérer de l'espace alloué
void freeNodeNom(nodeNom node) {
    if (node->suite)
        freeNodeNom(node->suite);
    if (node->autre)
        freeNodeNom(node->autre);
    if (node->feuilleNomPointeur->invariableSG)
        free(node->feuilleNomPointeur->invariableSG);
    if (node->feuilleNomPointeur->invariablePL)
        free(node->feuilleNomPointeur->invariablePL);
    if (node->feuilleNomPointeur->masSG)
        free(node->feuilleNomPointeur->masSG);
    if(node->feuilleNomPointeur->masPL)
        free(node->feuilleNomPointeur->masPL);
    if(node->feuilleNomPointeur->femSG)
        free(node->feuilleNomPointeur->femSG);
    if(node->feuilleNomPointeur->femPL)
        free(node->feuilleNomPointeur->femPL);
    free(node->feuilleNomPointeur);

    free(node);
    return;
}

//fonction qui creer chaque noeud
nodeNom createNodeNom(char theLettre)
{
    nodeNom nouv;


    nouv = (nodeNom)malloc(sizeof(struct node_nom));
    nouv->lettre = theLettre;
    nouv->suite = nouv->autre = NULL;
    nouv->feuilleNomPointeur = malloc(sizeof (struct feuilleNom));
    nouv->feuilleNomPointeur->femPL = nouv->feuilleNomPointeur->femSG  = nouv->feuilleNomPointeur->masPL = nouv->feuilleNomPointeur->masSG=NULL;
    nouv->feuilleNomPointeur->invariableSG = nouv->feuilleNomPointeur->invariablePL =NULL;
    //printf("creation du noeud %c \n" ,theLettre);

    return nouv;
}

//incrémentation de chaque nouveau mot dans l'arbre des mots
void upArbreNom(char* flechie, char* base, char* info, struct arbre_nom* arbre) {
    int i;
    nodeNom node;
    int taille = 0;
    int tailleFlechie = 0;
    for (i = 0; flechie[i] != '\0'; i++) {
        tailleFlechie++;
    }
    tailleFlechie = tailleFlechie + 1;
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
    for (i = 0; i < taille - 1; i++) {
        while (curseur->lettre != base[i] && curseur->autre != NULL) {
            curseur = curseur->autre;
        }
        if (curseur->lettre != base[i]) {
            node = createNodeNom(base[i]);
            curseur->autre = node;
            curseur = curseur->autre;
        }
        if (i != taille - 1) {
            if (!curseur->suite) {
                node = createNodeNom(base[i + 1]);
                curseur->suite = node;
            }
            curseur = curseur->suite;
        }
    }
    //creation de la feuille associée
    if (info[4] == 'M' && info[8] == 'S') {
        curseur->feuilleNomPointeur->masSG = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleNomPointeur->masSG, flechie, tailleFlechie);
        return;
    }
    if (info[4] == 'F' && info[8] == 'S') {
        curseur->feuilleNomPointeur->femSG = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleNomPointeur->femSG, flechie, tailleFlechie);
        return;
    }
    if (info[4] == 'M' && info[8] == 'P') {
        curseur->feuilleNomPointeur->masPL = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleNomPointeur->masPL, flechie, tailleFlechie);
        return;
    }
    if (info[4] == 'F' && info[8] == 'P') {
        curseur->feuilleNomPointeur->femPL = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleNomPointeur->femPL, flechie, tailleFlechie);
        return;
    }
    if (info[4] == 'I' && info[11] == 'S') {
        curseur->feuilleNomPointeur->invariableSG = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleNomPointeur->invariableSG, flechie, tailleFlechie);
        return;
    }
    if (info[4] == 'I' && info[11] == 'P') {
        curseur->feuilleNomPointeur->invariablePL = malloc(tailleFlechie * sizeof(char));
        memcpy(curseur->feuilleNomPointeur->invariablePL, flechie, tailleFlechie);
        return;
    }
    return;
}
//
void rechercheNom(nodeNom node, int *accord) {
    int nbAutre = 0;
    nodeNom curseur = node;
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
    if (node->feuilleNomPointeur->invariableSG != NULL || node->feuilleNomPointeur->invariablePL != NULL ||
        node->feuilleNomPointeur->masSG != NULL || node->feuilleNomPointeur->masPL != NULL ||
        node->feuilleNomPointeur->femSG != NULL || node->feuilleNomPointeur->femPL != NULL) {
        if (!node->suite) {
            int rd = aleatoireAutre(6);
            if (rd == 0 && node->feuilleNomPointeur->invariableSG != NULL) {
                printf("%s ", node->feuilleNomPointeur->invariableSG);
                *accord = 0;
                return;
            }
            if (rd == 1 && node->feuilleNomPointeur->invariablePL != NULL) {
                printf("%s ", node->feuilleNomPointeur->invariablePL);
                *accord = 1;
                return;
            }
            if (rd == 2 && node->feuilleNomPointeur->masSG != NULL) {
                printf("%s ", node->feuilleNomPointeur->masSG);
                *accord = 2;
                return;
            }
            if (rd == 3 && node->feuilleNomPointeur->masPL != NULL) {
                printf("%s ", node->feuilleNomPointeur->masPL);
                *accord = 3;
                return;
            }
            if (rd == 4 && node->feuilleNomPointeur->femSG != NULL) {
                printf("%s ", node->feuilleNomPointeur->femSG);
                *accord = 4;
                return;
            }
            if (rd == 5 && node->feuilleNomPointeur->femPL != NULL) {
                printf("%s ", node->feuilleNomPointeur->femPL);
                *accord = 5;
                return;
            } else
                rechercheNom(node, accord);
        }

        else {
            int continuer = aleatoireAutre(2);
            if (continuer == 0) {
                int rd = aleatoireAutre(6);
                if (rd == 0 && node->feuilleNomPointeur->invariableSG != NULL) {
                    printf("%s ", node->feuilleNomPointeur->invariableSG);
                    *accord = 0;
                    return;
                }
                if (rd == 1 && node->feuilleNomPointeur->invariablePL != NULL) {
                    printf("%s ", node->feuilleNomPointeur->invariablePL);
                    *accord = 1;
                    return;
                }
                if (rd == 2 && node->feuilleNomPointeur->masSG != NULL) {
                    printf("%s ", node->feuilleNomPointeur->masSG);
                    *accord = 2;
                    return;
                }
                if (rd == 3 && node->feuilleNomPointeur->masPL != NULL) {
                    printf("%s ", node->feuilleNomPointeur->masPL);
                    *accord = 3;
                    return;
                }
                if (rd == 4 && node->feuilleNomPointeur->femSG != NULL) {
                    printf("%s ", node->feuilleNomPointeur->femSG);
                    *accord = 4;
                    return;
                }
                if (rd == 5 && node->feuilleNomPointeur->femPL != NULL) {
                    printf("%s ", node->feuilleNomPointeur->femPL);
                    *accord = 5;
                    return;
                } else
                    rechercheNom(node, accord);
            } else {
                node = node->suite;
                rechercheNom(node, accord);
            }
        }
    }
    else{
        if(!node->suite)
            printf("erreur dans la recherche pas de suite");
        else{
            node = node->suite;
            rechercheNom(node, accord);
        }
    }
    return;
}
//permet de rechercher dans l'arbre nom un nom aléatoirement avec l'accord de la phrase
void rechercheAccordNom(nodeNom node,int *accord, int* correct){
    int nbAutre =0;
    nodeNom curseur = node;
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
    if(node->feuilleNomPointeur->invariableSG!=NULL || node->feuilleNomPointeur->invariablePL!=NULL || node->feuilleNomPointeur->masSG!=NULL || node->feuilleNomPointeur->masPL!=NULL || node->feuilleNomPointeur->femSG!=NULL ||node->feuilleNomPointeur->femPL!=NULL){
        if(!node->suite) {
            if(node->feuilleNomPointeur->invariableSG!=NULL && *accord == 0) {
                printf("%s ", node->feuilleNomPointeur->invariableSG);
                *correct = 1;
                return;
            }
            if(node->feuilleNomPointeur->invariablePL!=NULL && *accord == 1) {
                printf("%s ", node->feuilleNomPointeur->invariablePL);
                *correct = 1;
                return;
            }
            if ((*accord == 2 || *accord == 0) && node->feuilleNomPointeur->masSG != NULL) {
                printf("%s ", node->feuilleNomPointeur->masSG);
                *accord = 2;
                *correct = 1;
                return;
            }
            if ((*accord == 3 || *accord==1) && node->feuilleNomPointeur->masPL != NULL) {
                printf("%s ", node->feuilleNomPointeur->masPL);
                *accord = 3;
                *correct = 1;
                return;
            }
            if ((*accord == 4 || *accord == 0) && node->feuilleNomPointeur->femSG != NULL) {
                printf("%s ", node->feuilleNomPointeur->femSG);
                *accord = 4;
                *correct = 1;
                return;
            }
            if ((*accord == 5 || *accord==1) && node->feuilleNomPointeur->femPL != NULL) {
                printf("%s ", node->feuilleNomPointeur->femPL);
                *accord = 5;
                *correct = 1;
                return;
            }
        }
        else{

            int continuer = aleatoireAutre(2);
            if(continuer == 0){
                if(node->feuilleNomPointeur->invariableSG!=NULL && *accord == 0) {
                    printf("%s ", node->feuilleNomPointeur->invariableSG);
                    *correct = 1;
                    return;
                }
                if(node->feuilleNomPointeur->invariablePL!=NULL && *accord == 1) {
                    printf("%s ", node->feuilleNomPointeur->invariablePL);
                    *correct = 1;
                    return;
                }
                if ((*accord == 2 || *accord == 0) && node->feuilleNomPointeur->masSG != NULL) {
                    printf("%s ", node->feuilleNomPointeur->masSG);
                    *accord = 2;
                    *correct = 1;
                    return;
                }
                if ((*accord == 3 || *accord==1) && node->feuilleNomPointeur->masPL != NULL) {
                    printf("%s ", node->feuilleNomPointeur->masPL);
                    *accord = 3;
                    *correct = 1;
                    return;
                }
                if ((*accord == 4 || *accord == 0) && node->feuilleNomPointeur->femSG != NULL) {
                    printf("%s ", node->feuilleNomPointeur->femSG);
                    *accord = 4;
                    *correct = 1;
                    return;
                }
                if ((*accord == 5 || *accord==1)&& node->feuilleNomPointeur->femPL != NULL) {
                    printf("%s ", node->feuilleNomPointeur->femPL);
                    *accord = 5;
                    *correct = 1;
                    return;
                }
            }
            else{
                node = node->suite;
                rechercheAccordNom(node, accord, correct);
            }
        }
    }
    else{
        if(!node->suite){
            return;
        }
        else{
            node = node->suite;
            rechercheAccordNom(node, accord, correct);
        }
    }
    return;

}