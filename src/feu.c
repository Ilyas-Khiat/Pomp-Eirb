#include "common.h"

#include "feu.h"

int **init_feu(int *dim,int **map,int n) {
    int **map_feu = init_map(dim,0);
    for (int i = 0; i < dim[0]; i+=2)
    {
        for (int j = 0; j < dim[1]; j+=2)
        {
            if (rand() % n == 0 && map[i][j] != 0 )
            {
                map_feu[i][j] = 1;
            }
        } 
    }
    return map_feu;
}

void eteindre(Robot *robot) {
    robot->t_remplir -= 1;
    
    if ( robot->t_remplir <= 0)
    {
        robot->contenu = 0;
    }

}

void generate_feu(int **map_feu,int **map,int n,int *dim,int number_robot,Robot *robot[number_robot]) 
{
    int occupied = 0;
    
    int yf = rand() % dim[0] ;
    int xf = rand() % dim[1] ;

    for (int i = 0; i < number_robot; i++)
        {
            if (robot[i]->x == xf && robot[i]->y == yf){
                occupied = 1;
            }
        }

    if (rand() % n == 0 && occupied != 0 && map_feu[yf][xf] == 0 && map[yf][xf] != 0 )
    {
        map_feu[yf][xf] = 1;
    }
}