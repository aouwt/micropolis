#include <SDL.h>

#include "tile.h"
#include "map.h"
#include "sdl.h"

SDL_Surface *SDL_SpriteSheet = NULL;


SDL_Surface *SDL_RenderMap (SDL_Surface *surface, SDL_Rect Size, short TileSize, struct Map *Map) {
	
	if (surface != NULL) {
		if (
			(surface -> w < Size.w * TileSize) ||
			(surface -> h < Size.h * TileSize)
		) {
			SDL_FreeSurface (surface);
			surface = NULL;
		}
	}
	
	if (surface == NULL) {
		surface = SDL_CreateRGBSurface (
			0,
			Size.w * TileSize, Size.h * TileSize,
			0,
			0, 0, 0, 0
		);
	}
	
	for (int y = 0; y != Size.h; y ++) {
		for (int x = 0; x != Size.w; x ++) {
			tile_t tile = GetMapTile (Map, Size.x + x, Size.y + y).Tile;

			SDL_Rect srcrect = {
				((tile & 0xFF00) >> 8) * TileSize,
				(tile & 0x00FF) * TileSize,
				TileSize, TileSize
			};
			
			SDL_Rect dstrect = {
				x+Size.x * TileSize, y+Size.y * TileSize,
				TileSize, TileSize
			};
			SDL_BlitSurface (SDL_SpriteSheet, &srcrect, surface, &dstrect);
		}	
	}
	
	return surface;
}

