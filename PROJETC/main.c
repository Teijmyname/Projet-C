
#include "Adverbe.h"
#include "Nom.h"
#define ENTREE "C:\\Users\\Romain SAMSON\\Desktop\\Projet-C\\PROJETC\\dico_10_lignes.txt"
#define TAILLE_MAX 80

int main() {
    FILE * inputFile;
    srand( time( NULL ) );
    char* flechie= malloc(255*sizeof(char)); //[255]=""
    char* base= malloc(255*sizeof(char));
    char* info= malloc(255*sizeof(char));
    //int longueur = LongueurFichier(ENTREE);
    //inputFile = fopen (ENTREE, "r");
    //if (inputFile == NULL){
        //printf("erreur d'ouverture de fichier");
    //}
    errno_t err;
    struct arbre_adverbe arbreAdv;
    arbreAdv.racine = NULL;
    struct arbre_nom arbreN;
    arbreN.racine =NULL;
    int i = 0;
    FILE *Fi = fopen(ENTREE, "r");
    while (err = fscanf_s(Fi, "%s %s %s", flechie, 255, base, 255, info, 255) != EOF) {
        printf("%s %s %s\n", flechie, base, info);

        if(info[0]=='N')
            upArbreNom(flechie, base, info, &arbreN);
        /*if(info[0]=='V')
            upArbreVerbe();
        if(info[0]=='A'&&info[1]=='d'&&info[2]=='j')
            upArbreAdjectif();

*/
        if(info[0]=='A'&&info[1]=='d'&&info[2]=='v')
            upArbreAdverbe(base, &arbreAdv);
        else
            printf("   pas un nom\n");
        i++;
    }
    fclose(Fi);
    rechercheAdv(arbreAdv.racine);
    freeNodeAdv(arbreAdv.racine);
    rechercheNom(arbreN.racine);
    freeNodeNom(arbreN.racine);
    free(flechie);
    free(info);
    free(base);

    return 0;
}

