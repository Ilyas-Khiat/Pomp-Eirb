#include <SDL2/SDL_image.h>

#include "common.h"

#include "draw.h"

extern App app;

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;

	SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void drawRect(SDL_Color *clr,SDL_Rect rect)
{
	SDL_SetRenderDrawColor(app.renderer,clr->r,clr->g,clr->b,clr->a);
	SDL_RenderFillRect(app.renderer,&rect);
}

void drawMap(int **map,int *dim,SDL_Texture *montain,SDL_Texture *city,SDL_Texture *forest,SDL_Texture *water)
{
	for (int i = 0; i < dim[0]; i++)
	{
		for (int j = 0; j < dim[1]; j++)
		{
			SDL_Rect rect = {j*TILE_SIZE,i*TILE_SIZE,TILE_SIZE,TILE_SIZE};

			if (map[i][j] == 0)
			{
				blit(water,rect.x,rect.y);
				
			}
			if (map[i][j] == 1)
			{
				blit(montain,rect.x,rect.y);
				
			}
			if (map[i][j] == 2)
			{
				blit(city,rect.x,rect.y);
				
			}
			if (map[i][j] == 3)
			{
				blit(forest,rect.x,rect.y);
				
			}
			
		}
		
	}
	
}

void drawfire(int **map,int *dim,SDL_Texture *fire)
{
	for (int i = 0; i < dim[0]; i++)
	{
		for (int j = 0; j < dim[1]; j++)
		{
			SDL_Rect rect = {j*TILE_SIZE,i*TILE_SIZE,TILE_SIZE,TILE_SIZE};

			if (map[i][j] >= 1)
			{
				blit(fire,rect.x,rect.y);
			
			}
			
		}
		
	}
}

void drawText(int x,int y,char *str,SDL_Color color,int offsetX,int offsetY,TTF_Font* font,SDL_Texture* Message,SDL_Surface* surfaceMessage)
{
	surfaceMessage = TTF_RenderText_Solid(font,str, color); 

	Message = SDL_CreateTextureFromSurface(app.renderer, surfaceMessage);

	SDL_Rect Message_rect; 
	Message_rect.x = x + offsetX; 
	Message_rect.y = y + offsetY; 
	Message_rect.w = TILE_SIZE/2; 
	Message_rect.h = TILE_SIZE/2;

	SDL_RenderCopy(app.renderer, Message, NULL, &Message_rect);
	//free(surfaceMessage);
}
