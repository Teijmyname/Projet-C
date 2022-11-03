//
// Created by Teij Jayantilal on 24/10/2022.
//

#include "node.h"
struct arbre_adverbe createEmptyTree(){

    struct arbre_adverbe arbre;
    arbre.racine=NULL;
    return arbre;

}
nodeAdverbe createNodeAdv(char lettre, int taille)
{
    nodeAdverbe nouv;

    nouv = (nodeAdverbe)malloc(sizeof(struct node_adverbe));
    nouv->lettre = lettre;
    nouv->suite = nouv->autre = NULL;
    nouv->feuilleAdverbe = (char *)malloc(taille*sizeof (char));

    return nouv;
}

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
            upArbreAdverbe(base, arbre);
        else
            printf("   pas un adverbe\n");
        i++;
    }
        fclose(Fi);
    return;
}
void upArbreAdverbe(char* base,struct arbre_adverbe arbre){
    nodeAdverbe nouv;
    char* feuille;
    nouv = arbre.racine;
    int i;
    int taille=0;
    for (i=0;base[i]!='\0';i++){
        taille ++;
    }
    if(arbre.racine == NULL){
        for (i=0;base[i]!='\0';i++){
            nouv = createNodeAdv(base[i],taille);
            printf("%c",nouv->lettre);
            nouv = nouv->suite;

        }

        for(i = 0; i<taille;i++){
            nouv->feuilleAdverbe[i] = base[i];
            printf("ici");
        }
        printf("%c",nouv->feuilleAdverbe);

    }
    else{

        for( i=0; base[i]!='\0'; i++){
            while(nouv->lettre != base[i] && nouv!=NULL) {
                nouv = nouv->autre;
            }
            if(nouv == NULL){
                nouv = createNodeAdv(base[i],taille);
            }
            printf("%c",nouv->lettre);
            nouv=nouv->suite;
        }
        nouv->feuilleAdverbe = base;
    }
    return;
}
