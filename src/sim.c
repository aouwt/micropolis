#include <math.h>

#include "map.h"
#include "tile.h"
#include "micropolis.h"

/*float Sim_TotalAvgDist (struct Pair where, struct Map *map, tile_t tile) {
	size_t sz = 255;
	float *list = malloc (sz);
	long cnt = 0;
	
	for (long i = 0; i != map -> Len; i ++) {
		if (map -> Tile [i].Tile == tile) {
		
			GetMapXY (map, i, int x, int y);
			
			list [cnt] = sqrtf (powf (x, 2) + powf (y, 2));
			
			if (++ cnt >= sz)
				list = realloc (list, sz *= 2);
		}
	}
	
	return sum / (float) cnt;
}*/


struct Sim_Direction {
	float up, down, left, right;
}

struct Sim_Direction Sim_GetBestDirection (struct Pair start, struct Pair end) {
	float rad = atan2f (start.y - end.y, start.x - end.x);
	
	struct Sim_Direction dir;
	
	dir.right =	fabsf (rad - ((M_PI * 0.0) / 2.0)) % M_PI;
	dir.up =	fabsf (rad - ((M_PI * 1.0) / 2.0)) % M_PI;
	dir.left =	fabsf (rad - ((M_PI * 2.0) / 2.0)) % M_PI;
	dir.down =	fabsf (rad - ((M_PI * 3.0) / 2.0)) % M_PI;
	
	return dir;
}
long Sim_WalkRoads
