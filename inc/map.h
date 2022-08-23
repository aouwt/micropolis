#ifndef MAP_H
	#define MAP_H
	
	#include "tile.h"
	#include <stdlib.h>
	#include <stdint.h>
	
	#define GetLinearCoord(w, x, y) ( \
			((w) * (x)) + (y) \
		)
	
	#define GetXYCoord(i, w, x, y) { \
			x = (long) ((i) / (w)); \
			y = (i) % (w); \
		}
	
	#define GetMapXY(map, i, x, y) { \
			GetXYCoord ((i), (map) -> Width, (x), (y)); \
		}
	
	#define GetTile(map, x, y) ( \
			GetLinearCoord ((map) -> Width, (x), (y)) \
		)

	#define GetMapTile(map, x, y) ( \
			(map) -> Tile [GetTile ((map), (x), (y))] \
		)
	

	struct Map {
		struct Map_Tile {
			tile_t Tile;
			
			struct Map_Overlay {
				uint8_t Police;
				uint8_t Fire;
				float Happiness;
			} Overlay;
		} *Tile;
		int Width;
		int Height;
		long Len;
	};

	struct Map_Config {
		float Water;
		float Tree;
		float Grass;
		float Rock;
		
		float Sum;

		int Width;
		int Height;
	};
	
	struct Map_Margin {
		int top, bottom, left, right;
	};
	
	
	struct Map Map_Alloc (struct Map_Config *Config);
	long Map_GenerateTerrain (struct Map *Map, struct Map_Config* Config);
	tile_t Map_RandomTile (struct Map_Config *Config);
	struct Map *Map_ChangeMargins (struct Map *Map, struct Map_Margin Margin);
	

#endif
