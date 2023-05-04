
#include "common.h"

#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"
#include "carte.h"
#include "dijkstra.h"
#include "robot.h"
#include "feu.h"


App    app;
Robot *robot;

int main(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));

	initSDL();
	TTF_Init();

	SDL_Texture *montain = loadTexture("gfx/montains.PNG");
	SDL_Texture *city = loadTexture("gfx/city.PNG");
	SDL_Texture *forest = loadTexture("gfx/forest.PNG");
	SDL_Texture *water = loadTexture("gfx/water.PNG");

	SDL_Texture *fire = loadTexture("gfx/fire.png");
	SDL_Texture *waterdrop = loadTexture("gfx/waterdrop.png");

	SDL_Texture *robot = loadTexture("gfx/robot.png");

	SDL_Color black = {0,0,0};
	TTF_Font* font = TTF_OpenFont("gfx/Minecraft.ttf", 16);

	//CARTE//
	FILE *canal;
	canal=fopen(argv[1],"r");

	// load map //
	int *dim = taille(canal);

	printf("(%i,%i)\n",dim[0],dim[1]);
	int **map = init_map(dim,0);
	parser(canal,map,dim);

	fclose(canal);

	//init feu
	int **map_feu = init_feu(dim,map,3);

	FILE *robot_canal;
	robot_canal=fopen(argv[2],"r");
	int number_robots = get_number_robots(robot_canal);


	Robot **robots = malloc(sizeof(Robot)*number_robots);
	
	init_robots(robot_canal,number_robots,robots);

	for (int i = 0; i < number_robots; i++)
	{
		robots[i]->texture = robot;
		info_robot(robots[i]);
	}
	

	printf("robots init\n");
	
	atexit(cleanup);

	SDL_bool run = SDL_TRUE;
	while (run)
	{
		prepareScene();
		doInput(&run);
		drawMap(map,dim,montain,city,forest,water);
		drawfire(map_feu,dim,fire);
		for (int i = 0; i < number_robots; i++)
		{
			if (robots[i] != NULL)
			{
				if (robots[i]->state != -1)
				{
					robots[i]-> str = malloc(sizeof(char)*3);
					int_to_string(robots[i]->t_remplir,robots[i]->str);
					drawText(robots[i]->x_draw,robots[i]->y_draw,robots[i]->str,black,0,-(int) TILE_SIZE/2,font,robots[i]->Message,robots[i]->surfaceMessage);
					free(robots[i]->str);
				}
				
				if (robots[i]->state == 0)
				{
					int spot_water = find_spot(dim,map,robots[i]->x,robots[i]->y,0);
					robots[i]->end_coords = index_to_indices(spot_water,dim);
					printf("water(%i,%i)\n",robots[i]->end_coords[1],robots[i]->end_coords[0]);
					robots[i]->path = dijkstra(dim,map,map_feu,robots[i]->x,robots[i]->y,robots[i]->Vmontain,robots[i]->Vforest,robots[i]->Vcity,robots[i]->end_coords[1],robots[i]->end_coords[0]);
					robots[i]->next_coords = index_to_indices(robots[i]->path[robots[i]->i],dim); 
					robots[i]->state = 1;
				}

				if (robots[i]->state == 1)
				{
					deplacer(robots[i],robots[i]->next_coords[1],robots[i]->next_coords[0],map);
					if (robots[i]->t == -1)
					{
						robots[i]->state = 3;
						robots[i]->t = 0;
					}
					
				}

				if (robots[i]->state == 3)
				{
					robots[i]->i++;
					if (robots[i]->path[robots[i]->i] != -1)
					{
						free(robots[i]->next_coords);
						robots[i]->next_coords = index_to_indices(robots[i]->path[robots[i]->i],dim);
						printf("next(%i,%i)\n",robots[i]->end_coords[0],robots[i]->end_coords[1]);
						robots[i]->state = 1;
					}
					if (robots[i]->path[robots[i]->i] == -1)
					{
						printf("water found\n");
						robots[i]->i = 1;
						robots[i]->state = 4;
						free(robots[i]->next_coords);
						//free(robots[i]->path);
					}
				}
				if (robots[i]->state == 4)
				{
					remplir(robots[i]);
					blit(waterdrop,robots[i]->end_coords[1]*TILE_SIZE,robots[i]->end_coords[0]*TILE_SIZE);
					if (robots[i]->t_remplir >= robots[i]->capacite_max)
					{
						robots[i]->state = 5;
						printf("container full\n");
						free(robots[i]->end_coords);
						
					}
				}
				if (robots[i]->state == 5)
				{
					printf("searching fire ...\n");
					int spot_fire = find_spot(dim,map_feu,robots[i]->x,robots[i]->y,1);
					printf("spot: %i ...\n",spot_fire);
					if ( spot_fire == -1)
					{
						robots[i]->state = -1;
				
						printf("no fire left\n");
					}
					else {
						robots[i]->end_coords = index_to_indices(spot_fire,dim);
						printf("fire(%i,%i)\n",robots[i]->end_coords[1],robots[i]->end_coords[0]);
						
						robots[i]->path = dijkstra(dim,map,map_feu,robots[i]->x,robots[i]->y,robots[i]->Vmontain,robots[i]->Vforest,robots[i]->Vcity,robots[i]->end_coords[1],robots[i]->end_coords[0]);
						map_feu[robots[i]->end_coords[0]][robots[i]->end_coords[1]] = 2;
						robots[i]->next_coords = index_to_indices(robots[i]->path[robots[i]->i],dim); 
						robots[i]->state = 6;
						printf("path fire found\n");
					}
				}

				if (robots[i]->state == 6)
				{
					deplacer(robots[i],robots[i]->next_coords[1],robots[i]->next_coords[0],map);
					if (robots[i]->t == -1)
					{
						robots[i]->state = 7;
						robots[i]->t = 0;
					}
					
				}
				if (robots[i]->state == 7)
				{
					robots[i]->i++;
					if (robots[i]->path[robots[i]->i] != -1)
					{
						free(robots[i]->next_coords);
						robots[i]->next_coords = index_to_indices(robots[i]->path[robots[i]->i],dim);
						printf("next(%i,%i)\n",robots[i]->next_coords[0],robots[i]->next_coords[1]);
						robots[i]->state = 6;
					}
					if (robots[i]->path[robots[i]->i] == -1)
					{
						printf("fire found\n");
						robots[i]->i = 1;
						robots[i]->state = 8;
						free(robots[i]->next_coords);
						//free(robots[i]->path);

					}
				}
				if (robots[i]->state == 8)
				{
					eteindre(robots[i]);
					blit(waterdrop,robots[i]->end_coords[1]*TILE_SIZE,robots[i]->end_coords[0]*TILE_SIZE);
					if (robots[i]->t_remplir <= 0)
					{
						robots[i]->state = 0;
						map_feu[robots[i]->end_coords[0]][robots[i]->end_coords[1]] = -1;
						printf("feu eteint\n");
						free(robots[i]->end_coords);
						
					}
				}

				blit(robots[i]->texture,robots[i]->x_draw,robots[i]->y_draw);
			}
			
			
		}
		
		
		presentScene();

		SDL_Delay(0);
	}
	
	free(map);
	free(map_feu);
	for (int i = 0; i < number_robots; i++)
	{
		free(robots[i]->path);
	}
	free(dim);
	printf("Game OVER\n");
	cleanup();
	exit(1);
	return 0;
}

