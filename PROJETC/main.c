
#include "node.h"
#define ENTREE "C:\\Users\\Romain SAMSON\\Desktop\\Projet-C\\PROJETC\\dico_10_lignes.txt"
#define TAILLE_MAX 80

int main() {
    FILE * inputFile;
    char ligne[TAILLE_MAX];
    inputFile = fopen (ENTREE, "r");
    if (inputFile == NULL){
        printf("erreur d'ouverture de fichier");
    }
    while(fgets(ligne, TAILLE_MAX, inputFile)!= NULL){
        printf("%s", ligne);
    }

    fclose(inputFile);
    return 0;
}

