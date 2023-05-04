#include "common.h"
#include "robot.h"


Robot* init_robot(int capa_max,int x,int y,int Vf,int Vm,int Vc){
    Robot *mon_robot = malloc(sizeof(mon_robot));
    mon_robot->capacite_max = capa_max;
    mon_robot->x = x;
    mon_robot->y = y;
    mon_robot->Vcity = Vc;
    mon_robot->Vforest = Vf;
    mon_robot->Vmontain = Vm;
    mon_robot->t = 0;
    mon_robot->x_draw = mon_robot->x*TILE_SIZE;
    mon_robot->y_draw = mon_robot->y*TILE_SIZE;
    mon_robot->state = 0;
    mon_robot->Vremplissage = 1 ;
    mon_robot->t_remplir = 0;
    mon_robot->i = 1;
    mon_robot->path = NULL;
    mon_robot->next_coords = NULL;
    mon_robot->end_coords = NULL;
    return mon_robot;
}


void info_robot(Robot *robot){
    printf("capacity:%i\tx:%i\ty:%i,\t%i,\t%i,\t%i\n",robot->capacite_max,robot->x,robot->y,robot->Vcity,robot->Vforest,robot->Vmontain);
}

void deplacer(Robot *robot,int xe,int ye,int **map){
	if (map[ye][xe] == 1)
    {
        robot->t += 0.01*robot->Vmontain;
    }
    if (map[ye][xe] == 3)
    {
        robot->t += 0.01*robot->Vforest;
    }
    if (map[ye][xe] == 2)
    {
        robot->t += 0.01*robot->Vcity;
    }
	
	robot->x_draw = (robot->x + (xe - robot->x)*robot->t)*TILE_SIZE;
	robot->y_draw = (robot->y + (ye - robot->y)*robot->t)*TILE_SIZE;

	if (robot->t >= 1){
		robot->x = xe;
		robot->y = ye;

		robot->x_draw = xe*TILE_SIZE;
		robot->y_draw = ye*TILE_SIZE;
		robot->t = -1;
	}
}

void remplir(Robot *robot){
    robot->t_remplir += 1;
    if (robot->t_remplir >= robot->capacite_max)
    {
        robot->contenu = robot->capacite_max;
    }   
}

int get_number_robots(FILE *fichier){
	// je modifie l'argument pris par la fonction au lieu de char je mets un FILE*

	rewind(fichier);

	int n_largeur = 0;

    char c1 ='\0';

    c1 = fgetc(fichier);
    while(c1 != EOF){
        if ( c1== '\n')
        {
            n_largeur += 1;
        }
        c1 = fgetc(fichier);
    }
    n_largeur += 1;

    rewind(fichier);

    return n_largeur;
}

void init_robots(FILE *fichier, int dim,Robot *robots[dim]){

	rewind(fichier);

	char c ;
	int n = 0;

    int specs[6];

    char str[3];
	while (n < dim){
        
        for (int i = 0; i < 6; i++)
        {
            c = fgetc(fichier);
            str[0] = c;
            c = fgetc(fichier);
            str[1] = c;
            c = fgetc(fichier);
            str[2] = c;

            c = fgetc(fichier);
            
            specs[i] = atoi(str);
        }
        robots[n] = init_robot(specs[0],specs[1],specs[2],specs[3],specs[4],specs[5]);
        n++;
        	
	}
}


