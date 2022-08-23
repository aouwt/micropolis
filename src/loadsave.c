//#include <json-c.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "loadsave.h"
#include "map.h"
#include "tile.h"


struct LoadSave_Map {
	struct {
		uint16_t ver;
		
		uint64_t money;
		uint64_t debt;
		
		uint16_t map_w, map_h;
	} stat;

	tile_t *map;
};


struct LoadSave_Map *LoadSave_LoadFile (const char *path, struct LoadSave_Map *map) {
	int fd = open (path, O_RDONLY);
	if (fd == -1) {
		perror ("open");
		return NULL;
	}
	
	struct stat stat;
	fstat (fd, &stat)
	
	if (sizeof (map -> stat) != read (fd, (void *) &(map -> stat), sizeof (map -> stat)))
		goto error;
	
	
	size_t map_sz = sizeof (tile_t) * map -> stat.map_w * map -> stat.map_h;
	map -> map = (tile_t *) malloc (map_sz);
	if (map -> map == NULL) {
		perror ("malloc");
		goto error;
	}
	
	if (map_sz != read (fd, (void *) map -> map, map_sz))
		goto error;

	return map;
	
	error:
	close (fd);
	free (map -> map);
	return NULL;
}


struct Map LoadSave_PrepareMap (struct LoadSave_Map *map) {
	struct Map out;
	out.Width = map -> stat.map_w;
	out.Height = map -> stat.map_h;
	
	out.Len = out.Width * out.Height;
	out.Tile = (struct Map_Tile *) calloc (out.Len, sizeof (struct Map_Tile));
	
	for (long i = 0; i != out.Len; i ++)
		out.Tile [i].Tile = map -> map [i];
	return out;
}
