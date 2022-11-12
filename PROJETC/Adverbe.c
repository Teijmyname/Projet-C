//
// Created by Teij Jayantilal on 24/10/2022.
//

#include "Adverbe.h"
//creation de nouveau noeud
nodeAdverbe createNodeAdv(char theLettre, int theTaille)
{
    nodeAdverbe nouv;

    nouv = (nodeAdverbe)malloc(sizeof(struct node_adverbe));
    nouv->lettre = theLettre;
    nouv->suite = nouv->autre = NULL;
    nouv->feuilleAdverbe = NULL;

    return nouv;
}
//libere l'espace utilisé
void freeNodeAdv(nodeAdverbe node){
    if(node->suite)
        freeNodeAdv(node->suite);
    if(node->autre)
        freeNodeAdv(node->autre);
    if(node->feuilleAdverbe){
        free(node->feuilleAdverbe);
    }
    free(node);
    return;
}
// fonction pour mettre à jour l'arbre avec les adverbes et leur forme fléchie(la forme fléchie dans la feuille)
void upArbreAdverbe(char* base,struct arbre_adverbe *arbre) {
    int i;
    nodeAdverbe node;
    int taille = 0;
    for (i = 0; base[i] != '\0'; i++) {
        taille++;
    }
    //on pointe node sur la première lettre du mot que nous voulons implémenter dans l'arbre
    if (!arbre->racine) {
        arbre->racine = createNodeAdv(base[0],taille);
    }
    //nous allons implémenter les autres jusqu'à la dernière
    // apres chaque mot retour en haut de l'arbre
    nodeAdverbe curseur;
    curseur = arbre->racine;
    for(i=0;i<taille-1;i++) {
        while (curseur->lettre != base[i] && curseur->autre != NULL) {
            curseur = curseur->autre;
        }
        if (curseur->lettre != base[i]) {
            node = createNodeAdv(base[i], taille);
            //printf("stockage dans le dernier suivant de la lettre %c\n", node->lettre);
            curseur->autre = node;
            curseur = curseur->autre;
        }
        if(i != taille-1) {
            if (!curseur->suite) {
                node = createNodeAdv(base[i+1], taille);
                curseur->suite = node;
            }
            curseur = curseur->suite;
        }
    }
    curseur->feuilleAdverbe = malloc(taille+1 * sizeof(char));
    memcpy(curseur->feuilleAdverbe, base, taille+1);
    return;
}
//recherche aléatoirement un adverbe dans l'arbre
void rechercheAdv(nodeAdverbe node){
    int nbAutre =0;
    nodeAdverbe curseur = node;
    while(curseur->autre){
        nbAutre ++;
        curseur=curseur->autre;
    }
    if(nbAutre != 0) {
        int i = 0;
        int rd = aleatoireAutre(nbAutre+1);
        while (i != rd) {
            i++;
            node = node->autre;
        }
    }
    if(node->feuilleAdverbe!=NULL){
        if(!node->suite) {
            printf("%s ", node->feuilleAdverbe);
            return;
        }
        else{
            int continuer = aleatoireAutre(2);
            if(continuer == 0){
                printf("%s ",node->feuilleAdverbe);
                return;
            }
            else{
                node = node->suite;
                rechercheAdv(node);
            }
        }
    }
    else{
        if(!node->suite)
            printf("erreur dans la recherche pas de suite");
        else{
            node = node->suite;
            rechercheAdv(node);
        }
    }
    return;

}
//fonction qui retourne un entier aléatoire entre 0 et NbAutre-1
int aleatoireAutre(int NbAutre){
    int tailleAutre = rand() % NbAutre;
    return tailleAutre;
}