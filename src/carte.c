#include "common.h"

#include "carte.h"

int *taille(FILE *fichier){
	// je modifie l'argument pris par la fonction au lieu de char je mets un FILE*

	rewind(fichier);
	
	int *dimension = (int *)malloc(sizeof(int) * 2);

	int p_longueur= 0;
	int n_largeur = 0;

    char c1 ='\0';
    char c2='\0';

    c1 = fgetc(fichier);
    while(c1!= EOF){
        if ( c1=='\n')
        {
            n_largeur += 1;
        }
        c1 = fgetc(fichier);
    }
    n_largeur += 1;

    rewind(fichier);

    c2 = fgetc(fichier);
    while( (c2!='\n')){

    	if (c2 != ' ')
    	{
    		p_longueur +=1;
    	}
    	
    	c2 = fgetc(fichier);
     
    }
    dimension[0]=n_largeur;
    dimension[1]=p_longueur;

    return dimension;
}


void parser(FILE *fichier, int **map , int *dimension){

	rewind(fichier);

	char c = fgetc(fichier);
	int n = 0 , p = 0;

	while (n < dimension[0]){
		while (p < dimension[1])
		{
			if ( isdigit(c))
			{
				map[n][p] = atoi(&c);
				p++;
			}
			c = fgetc(fichier);
		}
		n++;
		p = 0;	
	}
}

