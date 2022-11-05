//
// Created by Teij Jayantilal on 24/10/2022.
//

#include "node.h"
//creation de nouveau noeud
nodeAdverbe createNodeAdv(char theLettre, int theTaille)
{
    nodeAdverbe nouv;

    nouv = (nodeAdverbe)malloc(sizeof(struct node_adverbe));
    nouv->lettre = theLettre;
    nouv->suite = nouv->autre = NULL;
    nouv->feuilleAdverbe = NULL;
    printf("creation du noeud %c \n" ,theLettre);

    return nouv;
    /*struct node_adverbe nouv = {.feuilleAdverbe=NULL, .lettre = theLettre, .suite = NULL, .autre =NULL};
    nodeAdverbe node;
    printf("creation du noeud %c \n" ,nouv.lettre);
    node = &nouv;
    return node;*/
}
//fonction qui permet d'extaire les mot d'une ligne dans 3 tableaux puis de les placer dans les arbres associés
void extraireFichier(char* Fichier, char* flechie, char* base, char* info) {
    errno_t err;
    struct arbre_adverbe arbre;
    arbre.racine = NULL;
    int i = 0;
    FILE *Fi = fopen(Fichier, "r");
    while (err = fscanf_s(Fi, "%s %s %s", flechie, 255, base, 255, info, 255) != EOF) {
        printf("%s %s %s\n", flechie, base, info);

        /*if(info[0]=='N')
            upArbreNom();
        if(info[0]=='V')
            upArbreVerbe();
        if(info[0]=='A'&&info[1]=='d'&&info[2]=='j')
            upArbreAdjectif();

*/
        if(info[0]=='A'&&info[1]=='d'&&info[2]=='v')
            upArbreAdverbe(base, &arbre);
        else
            printf("   pas un adverbe\n");
        i++;
    }
    fclose(Fi);
    rechercheAdv(arbre.racine);
    freeNodeAdv(arbre.racine);

    return;
}
void freeNodeAdv(nodeAdverbe node){
    if(node->suite)
        freeNodeAdv(node->suite);
    if(node->autre)
        freeNodeAdv(node->autre);
    if(node->feuilleAdverbe)
        free(node->feuilleAdverbe);
    free(node);
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
            printf("stockage dans le dernier suivant de la lettre %c\n", node->lettre);
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
    curseur->feuilleAdverbe = createFeuilleAdv(base,taille);
    printf("Feuille %s\n", curseur->feuilleAdverbe);
    return;
}
char* createFeuilleAdv(char* base, int taille) {
    char* feuille = malloc(taille * sizeof(char));
    strcpy(feuille,base);
    return feuille;
}
void rechercheAdv(nodeAdverbe node){
    printf("debut recherche adv\n");
    int nbAutre =0;
    nodeAdverbe curseur = node;
    while(curseur->autre){
        nbAutre ++;
        curseur=curseur->autre;
    }
    printf("nbAutre = %d\n",nbAutre);
    if(nbAutre != 0) {
        int i = 0;
        int rd = aleatoireAutre(nbAutre);
        while (i != rd) {
            i++;
            node = node->autre;
        }
    }
    printf("%c\n",node->lettre);
    if(node->feuilleAdverbe){
        if(!node->suite) {
            printf("%s", node->feuilleAdverbe);
            return;
        }
        else{
            int continuer = aleatoireAutre(1);
            if(continuer == 0){
                printf("%s",node->feuilleAdverbe);
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

    /*}
    if(node->suite){
        int rd = aleatoireAutre(2);
        if(rd==0)
            printf("s",node->feuilleAdverbe);
        else
            node = node->suite;
    }*/

}
int aleatoireAutre(int NbAutre){
    int tailleAutre = rand() % NbAutre+1;
    printf("%d",tailleAutre);
    return tailleAutre ;
}
