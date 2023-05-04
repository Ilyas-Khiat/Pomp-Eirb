#include "common.h"

#include "input.h"

void doInput(SDL_bool *run)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				*run = SDL_FALSE;
				break;

			default:
				break;
		}
	}
}
