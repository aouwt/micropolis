#include <stdlib.h>
#include <stdio.h>

#include "map.h"


struct Map Map_Alloc (struct Map_Config *Config) {
	struct Map map;
	map.Width = Config -> Width;
	map.Height = Config -> Height;
	
	map.Len = map.Width * map.Height;
	
	map.Tile = (struct Map_Tile *) calloc (map.Len, sizeof (struct Map_Tile));
}


long Map_GenerateTerrain (struct Map *Map, struct Map_Config *Config) {
	long count = 0;
	
	/*Config -> Sum =
		Config -> Water +
		Config -> Tree +
		Config -> Grass +
		Config -> Rock;*/
			
	for (int y = 0; y != Map -> Height; y ++) {
		for (int x = 0; x != Map -> Width; x ++) {
			
			
			#define GetTileOver(dx, dy) ( \
					( /* Is out of margin? */\
						((dx + x) >= 0 && ((dx + x) < Map -> Width)) && \
						((dy + y) >= 0 && ((dy + y) < Map -> Height)) \
					) ? \
						GetMapTile (Map, dx + x, dy + y) /* Grab the tile */ : \
						Map_RandomTile (Config) /* Get random tile */ \
				)
			
			if (GetMapTile (Map, x, y).Tile == TILE_NULL) {
			}
			
			#undef GetTileOver
		}
	}
}

tile_t Map_RandomTile (struct Map_Config *Config) {
	float mult = ((float) RAND_MAX) / (
		Config -> Water	+
		Config -> Tree	+
		Config -> Grass	+
		Config -> Rock
	);
	
	int water	=	Config -> Water	* mult;
	int tree	=	Config -> Tree	* mult + water;
	int grass	=	Config -> Grass	* mult + tree;
	int rock	=	Config -> Rock	* mult + grass;
	
	int r = rand ();
	
	if (r > rock)
		return TILE_ROCK;
	else
	if (r > grass)
		return TILE_GRASS;
	else
	if (r > tree)
		return TILE_TREE;
	else
	if (r > water)
		return TILE_WATER;
	else {
		fprintf (stderr, "Impossible situation encountered on line %i. Exiting.\n", __LINE__);
		exit (127);
		return TILE_NULL;
	}
}

struct Map *Map_ChangeMargins (struct Map *Map, struct Map_Margin Margin) {
	struct Map newmap;
	newmap.Width = Margin.left + Margin.right + Map -> Width;
	newmap.Height = Margin.top + Margin.bottom + Map -> Height;
	newmap.Len = newmap.Width * newmap.Height;
	newmap.Tile = calloc (newmap.len, sizeof (struct Map_Tile));
	
	for (int y = 0; y != Map -> Height; y ++) {
		int ny = y - Margin.top;
		
		if (ny < 0 || y < 0)
			continue;
		else
		if (ny >= newmap.Height || y >= Map -> Height)
			break;
		
		for (int x = 0; x != Map -> Width; x ++) {
			int nx = x - Margin.left;
			
			if (nx < 0 || x < 0)
				continue;
			else
			if (nx >= newmap.Width || x >= Map -> Width)
				break;
			
			newmap.Tile [GetLinearCoord (newmap.Width, nx, ny)] = GetMapTile (Map, x, y);
		}
	}
	
	free (Map -> Tile);
	*Map = newmap;
	return Map;
}

