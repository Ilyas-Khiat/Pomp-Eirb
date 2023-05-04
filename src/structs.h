typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window   *window;
} App;

typedef struct
{
	int          x;
	int          y;
	SDL_Texture *texture;
	int vitesse;
} Entity;

typedef struct Robot{
    int state;
    int x; /* la position du robot qui sera le coefficient de la colonne de la matrice */
    int y; /* la position du robot qui sera le coefficient de la ligne de la matrice */
    int vitesse; /* vitesse du robot */
    int Vremplissage;
    int Vmontain;
    int Vforest;
    int Vcity;
    float t;
    int x_draw;
    int y_draw;
    SDL_Texture *texture;
    int capacite_max;
    int contenu;
    int t_remplir;
    int *next_coords;
    int i;
    int *path;
    int *end_coords;
    char *str;
    SDL_Texture* Message;
    SDL_Surface* surfaceMessage;
}Robot;

typedef struct Feu{
	int x;
	int y;
	int taille;
	int t_eteindre;
}Feu;