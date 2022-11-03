
#include "node.h"
#define ENTREE "C:\\Users\\Romain SAMSON\\Desktop\\Projet-C\\PROJETC\\dico_10_lignes.txt"
#define TAILLE_MAX 80

int main() {
    FILE * inputFile;

    char flechie[255]="";
    char base[255]="";
    char info[255]="";
    //int longueur = LongueurFichier(ENTREE);
    for (int i = 0; i < 80; i++)
    {

    }
    inputFile = fopen (ENTREE, "r");
    if (inputFile == NULL){
        printf("erreur d'ouverture de fichier");
    }
    extraireFichier(ENTREE,flechie,base,info);
    fclose(inputFile);
    return 0;
}

