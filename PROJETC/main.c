
#include "node.h"
#define ENTREE "C:\\Users\\Romain SAMSON\\Desktop\\Projet-C\\PROJETC\\dico_10_lignes.txt"
#define TAILLE_MAX 80

int main() {
    FILE * inputFile;
    srand( time( NULL ) );
    char* flechie= malloc(255*sizeof(char)); //[255]=""
    char* base= malloc(255*sizeof(char));
    char* info= malloc(255*sizeof(char));
    //int longueur = LongueurFichier(ENTREE);
    inputFile = fopen (ENTREE, "r");
    if (inputFile == NULL){
        printf("erreur d'ouverture de fichier");
    }

    extraireFichier(ENTREE,flechie,base,info);
    fclose(inputFile);
    free(flechie);
    free(info);
    free(base);

    return 0;
}

