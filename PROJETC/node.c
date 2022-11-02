//
// Created by Teij Jayantilal on 24/10/2022.
//

#include "node.h"
nodeAdverbe createNodeAdv(char lettre)
{
    nodeAdverbe nouv;

    nouv = (nodeAdverbe)malloc(sizeof(struct node_adverbe));
    nouv->lettre = lettre;
    nouv->suite = nouv->autre = NULL;

    return nouv;
}

void extraireFichier(char* Fichier, char* flechie, char* base, char* info) {
    errno_t err;
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
        else
            printf("erreur dans l'impémentation de l'arbre");
     */
        i++;
    }
        fclose(Fi);
}
void upArbreAdverbe(char* base){
    struct arbre_adverbe arbre;
    nodeAdverbe nouv;
    nouv = arbre.racine;

    if(arbre.racine == NULL){
        for (int i=0;base[i]!='\0';i++){
            nouv = createNodeAdv(base[i]);
            nouv = nouv->suite;
        }
        nouv->feuilleAdverbe = base;
    }
    else{
        for(int i=0; i<base[i]!='\0'; i++){
            while(nouv->lettre != base[i] || nouv!=NULL) {
                nouv = nouv->autre;
            }
            if(nouv == NULL){
                nouv = createNodeAdv(base[i]);
            }
            nouv=nouv->suite;
        }
    }
}
