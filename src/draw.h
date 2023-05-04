void         prepareScene(void);
void         presentScene(void);

SDL_Texture *loadTexture(char *filename);
void         blit(SDL_Texture *texture, int x, int y);
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
void drawRect(SDL_Color *clr,SDL_Rect rect);

void drawMap(int **map,int *dim,SDL_Texture *montain,SDL_Texture *city,SDL_Texture *forest,SDL_Texture *water);
void drawfire(int **map,int *dim,SDL_Texture *fire);

void drawText(int x,int y,char *str,SDL_Color color,int offsetX,int offsetY,TTF_Font* font,SDL_Texture* Message,SDL_Surface* surfaceMessage);