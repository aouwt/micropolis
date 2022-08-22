#ifndef MAP_H
	#define MAP_H
	
	#include "tile.h"
	#include <stdlib.h>
	#include <stdint.h>
	
	#define GetLinearCoord(w, x, y) ( \
			((w) * (x)) + (y) \
		)

	#define GetTile(map, x, y) ( \
			GetLinearCoord ((map) -> Width, (x), (y)) \
		)

	#define GetMapTile(map, x, y) ( \
			(map) -> Tile [GetTile (map, x, y)] \
		)

	struct Map {
		struct MapTile {
			tile_t Tile;
			
			struct MapOverlay {
				uint8_t Electric;
				uint8_t Water;
				uint8_t Sewage;
				uint8_t Police;
				uint8_t Fire;
			} Overlay;
		} *Tile;
		int Width;
		int Height;
	};

	struct MapConfig {
		float Water;
		float Tree;
		float Grass;
		float Rock;
		
		float Sum;

		int Width;
		int Height;
	};
	
	struct Margin {
		int top, bottom, left, right;
	};
	
	
	struct Map Map_Alloc (struct MapConfig *Config);
	long Map_GenerateTerrain (struct Map *Map, struct MapConfig* Config);
	tile_t Map_RandomTile (struct MapConfig* Config);
	struct Map *Map_ChangeMargins (struct Map *Map, struct Margin Margin);
	

#endif
