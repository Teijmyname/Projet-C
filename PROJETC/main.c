
#include "Adverbe.h"
#include "Nom.h"
#include "Adjectif.h"
#include "Verbe.h"
//Définition des constantes regroupants les fichiers txt à ouvrir
#define ENTREE "C:\\Users\\Romain SAMSON\\Desktop\\Projet-C\\PROJETC\\dico_10_lignes.txt"
#define TOUS "C:\\Users\\Romain SAMSON\\Desktop\\Projet-C\\PROJETC\\dictionnaire_non_accentue.txt"
//initialisation des variables globales
//accord permet de savoir l'accord à utilisé en paramètre de fonction
int accord = 0;
//correct est une variable utilisé lors de la recherche dans un arbre, mis à 1 si tout est correct
int correct = 0;
int main() {
    //initialisation des variables
    srand( time( NULL ) );
    char* flechie= malloc(255*sizeof(char));
    char* base= malloc(255*sizeof(char));
    char* info= malloc(255*sizeof(char));
    struct arbre_adverbe arbreAdv;
    arbreAdv.racine = NULL;
    struct arbre_nom arbreN;
    arbreN.racine =NULL;
    struct arbre_adjectif arbreAdj;
    arbreAdj.racine = NULL;
    struct arbre_verbe arbreV;
    arbreV.racine = NULL;
    int choix1;
    int i;
    int taille;
    //Ouverture du fichier séléctioné et séparation de chaque ligne en trois chaines de caractères
    FILE *Fi = fopen(TOUS, "r");
    while ( fscanf_s(Fi, "%s %s %s", flechie, 255, base, 255, info, 255) != EOF) {
        taille =0;
        for(i = 0; info[i] != '\0';i++)
            taille ++;
        //Incrémentation ligne par ligne du fichier dans les arbres associés
        if(info[0]=='A'&&info[1]=='d'&&info[2]=='v')
            upArbreAdverbe(base, &arbreAdv);
        if(info[0]=='N')
            upArbreNom(flechie, base, info, &arbreN);
        if(info[0]=='A'&&info[1]=='d'&&info[2]=='j') {
            upArbreAdjectif(flechie, base, info, &arbreAdj);
        }
        if(info[0]=='V' && info[taille-1] == '3'&& info[4]=='I'&&info[5]=='I'&&info[6]=='m'&&info[7]=='p'){
            upArbreVerbe(flechie, base, info, &arbreV);
        }
        if(info[0]=='V' && info[taille-1] == '3'&& info[4]=='I'&&info[5]=='P'&&info[6]=='r'&&info[7]=='e'){
            upArbreVerbe(flechie, base, info, &arbreV);
        }
        if(info[0]=='V' && info[taille-1] == '3'&& info[4]=='S'&&info[5]=='P'&&info[6]=='r'&&info[7]=='e'){
            upArbreVerbe(flechie, base, info, &arbreV);
        }
    }
    fclose(Fi);
    //choisir dans le menu principal entre les differentes possilités de formation de phrase
    do{
        printf("\nVeuillez choisir entre ces 3 modeles de phrases:\n\n");
        printf("Tapez 1 pour le modele: nom adjectif verbe nom\n");
        printf("Tapez 2 pour le modele: nom qui verbe verbe nom adjectif\n");
        printf("Tapez 3 pour le modele: nom verbre adverbe nom adjectif\n");
        scanf("%d", &choix1);
    }while(choix1<1 || choix1>3);
    if(choix1==1){
        printf("Vous venez de tapez 1 pour le modele: nom adjectif verbe nom !\n\n");
        rechercheNom(arbreN.racine, &accord);
        while(correct !=1){
            nodeAdjectif node = arbreAdj.racine;
            rechercheAccordAdjectif(node, &accord, &correct);
        }
        correct= 0;
        while(correct !=1) {
            nodeVerbe node = arbreV.racine;
            rechercheAccordVerbe(node, &accord, &correct);
        }
        correct= 0;
        while(correct !=1) {
            nodeNom node = arbreN.racine;
            rechercheAccordNom(node, &accord, &correct);
        }
    }
    if(choix1 == 2){
        printf("Vous venez de tapez 2 pour le modele: nom qui verbe verbe nom adjectif !\n\n");
        rechercheNom(arbreN.racine, &accord);
        printf("qui ");
        correct= 0;
        while(correct !=1) {
            nodeVerbe node = arbreV.racine;
            rechercheAccordVerbe(node, &accord, &correct);
        }
        correct= 0;
        while(correct !=1) {
            nodeVerbe node = arbreV.racine;
            rechercheAccordVerbe(node, &accord, &correct);
        }
        correct= 0;
        while(correct !=1) {
            nodeNom node = arbreN.racine;
            rechercheAccordNom(node, &accord, &correct);
        }
        correct= 0;
        while(correct !=1){
            nodeAdjectif node = arbreAdj.racine;
            rechercheAccordAdjectif(node, &accord, &correct);
        }
    }
    if(choix1 == 3){
        printf("Vous venez de tapez 3 pour le modele: nom verbre adverbe nom adjectif\n\n");
        rechercheNom(arbreN.racine, &accord);
        correct= 0;
        while(correct !=1) {
            nodeVerbe node = arbreV.racine;
            rechercheAccordVerbe(node, &accord, &correct);
        }
        rechercheAdv(arbreAdv.racine);
        correct= 0;
        while(correct !=1) {
            nodeNom node = arbreN.racine;
            rechercheAccordNom(node, &accord, &correct);
        }
        correct= 0;
        while(correct !=1){
            nodeAdjectif node = arbreAdj.racine;
            rechercheAccordAdjectif(node, &accord, &correct);
        }
    }
    // on libère tout l'espace qu'on a alloué
    freeNodeAdjectif(arbreAdj.racine);
    freeNodeAdv(arbreAdv.racine);
    freeNodeNom(arbreN.racine);
    freeNodeVerbe(arbreV.racine);
    free(flechie);
    free(info);
    free(base);

    return 0;
}

