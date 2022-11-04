//
// Created by Teij Jayantilal on 24/10/2022.
//

#include "node.h"
struct arbre_adverbe createEmptyTree(){

    struct arbre_adverbe arbre;
    //arbre.racine= malloc(sizeof (struct node_adverbe));
    arbre.racine=NULL;
    return arbre;

}
//creation de nouveau noeud
nodeAdverbe createNodeAdv(char theLettre, int theTaille)
{
    struct node_adverbe nouv = {.feuilleAdverbe=(char *) malloc(theTaille* sizeof(char)), .lettre = theLettre, .suite = NULL, .autre =NULL};
    nodeAdverbe node;
    node = &nouv;
    return node;
}
//fonction qui permet d'extaire les mot d'une ligne dans 3 tableaux puis de les placer dans les arbres associés
void extraireFichier(char* Fichier, char* flechie, char* base, char* info) {
    errno_t err;
    struct arbre_adverbe arbre;
    arbre = createEmptyTree();
    int i = 0;
    FILE *Fi = fopen(Fichier, "r");
    while (err = fscanf_s(Fi, "%s %s %s", flechie, 255, base, 255, info, 255) != EOF) {
        printf("%s %s %s\n", flechie, base, info);

        /*if(info[0]=='N')
            upArbreNom();
        if(info[0]=='V')
            upArbreVerbe();
        if(info[0]=='A'&&info[1]=='d'&&info[2]=='v')
            upArbreAdverbe(base);
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
    //on initialise le noeud avec node son pointeur de noeud
    struct node_adverbe nouv = {.feuilleAdverbe=(char *) malloc(taille* sizeof(char)), .lettre = base[taille-1], .suite = NULL, .autre =NULL};
    node = &nouv;
//si l'arbre est vide alors on implémente notre premier Adv dans l'arbre avec sa feuille
    if (arbre->racine == NULL) {
        arbre->racine = createNodeAdv(base[0],taille);
        node = arbre->racine;
        printf("%c", node->lettre);
        node = node->suite;
        for (i = 1; base[i] != '\0'; i++) {
            node = createNodeAdv(base[i], taille);
            printf("%c", node->lettre);
            node = node->suite;
        }
        for(i=0;i<taille;i++) {
            nouv.feuilleAdverbe[i] = base[i];
            //printf("%c",nouv.feuilleAdverbe[i]);
        }
        printf(" premier Adv ! \n");
        }
//sinon la racine de l'arbre n'est pas vide alors on implémente les autres adverbes dans l'arbre
    else{
        node = arbre->racine;
        for( i=0; base[i]!='\0'; i++){
            while(node->lettre != base[i] && node->autre !=NULL) {
                node = node->autre;
            }
            if(node->autre == NULL){
                node = createNodeAdv(base[i],taille);
            }
            printf("%c",node->lettre);
            node=node->suite;
        }
        for(i=0;i<taille;i++) {
            nouv.feuilleAdverbe[i] = base[i];
            //printf("%c",nouv.feuilleAdverbe[i]);
        }
        printf(" autres Adv !\n");
    }
    free(nouv.feuilleAdverbe);
    return;
}
