#ifndef SDL_H
	#define SDL_H
	
	#include <SDL.h>
	#include "tile.h"
	#include "map.h"
	
	extern SDL_Surface *SDL_SpriteSheet;
	
	SDL_Surface *SDL_RenderMap (SDL_Surface *surface, SDL_Rect Size, short TileSize, struct Map *Map);
#endif
