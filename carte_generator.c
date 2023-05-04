#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int **init_matrice(int *dimension){
    int i, j;
    int n_lignes = dimension[0];
    int p_colonnes = dimension[1];
    
    int **matrice = (int **)malloc(n_lignes * sizeof(int *));
    
    for (i = 0; i < n_lignes; i++) {

        matrice[i] = (int *)malloc(p_colonnes * sizeof(int));
        for (j = 0; j < p_colonnes; j++) {

            matrice[i][j] = 0;
        }
    }
    
    return matrice;
}


int **create_map(int *dimension, int **matrice){

	int nb_lignes = dimension[0];
    int nb_colonnes = dimension[1];
    for (int i = 0; i < nb_lignes; i++) {
       for (int j = 0; j < nb_colonnes; j++) {
         if (rand() % 10  == 0)
         {
            matrice[i][j] = 0;
         }
         else {
            matrice[i][j] = rand() % 3 + 1;
         }
        } 
    }
    return matrice;
}



// void ecrire(FILE *f, int **matrice, int *dimension){
//    for (int i = 0; i < dimension[0]; i++) {
//         for (int j = 0; j < dimension[1]; j++) {
//         	fprintf(f, "%d ", matrice[i][j]);
//       	}
//       	fprintf(f,"\n");
//    }
// }


void ecrire(FILE *f, int **matrice, int *dimension){
   for (int i = 0; i < dimension[0]; i++) {
      if (i!=dimension[0]-1){
         for (int j = 0; j < dimension[1]; j++){
            if (j!=dimension[1]-1){
               fprintf(f, "%d ", matrice[i][j]);
            }
            else{
               fprintf(f, "%d", matrice[i][j]);
            }
         }
         fprintf(f, "\n"); 
      }
      else{
         for (int j = 0; j < dimension[1]; j++){
            if (j!=dimension[1]-1){
               fprintf(f, "%d ", matrice[i][j]);
            }
            else{
               fprintf(f, "%d", matrice[i][j]);
            }
         }
      }

   }
}


int main() {


	int n_lignes;
	int p_colonnes;
   
   printf("Dimension de la carte: \n");
   printf(" --> Entrez la largeur (nbr de lignes) : ");
   scanf("%d", &n_lignes);
   printf(" --> Entrez la longeur (nbr de colonnes) : ");
   scanf("%d", &p_colonnes);

   int *taille = (int *)malloc(sizeof(int) * 2);
   taille[0] = n_lignes;
   taille[1] = p_colonnes;


   FILE *canal = fopen("carte_generated.txt", "w");


   int **map = create_map(taille,init_matrice(taille));

   ecrire(canal,map,taille);

   for (int i = 0; i < n_lignes; i++) {

      free(map[i]);
    }

   free(map);
   
   fclose(canal);
   
   return 0;
}



