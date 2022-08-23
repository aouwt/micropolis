#include <math.h>

#include "map.h"
#include "tile.h"
#include "micropolis.h"

float Sim_TotalAvgDist (struct Pair where, struct Map *map, tile_t tile) {
	float sum = 0;
	long cnt = 0;
	for (long i = 0; i != map -> Len; i ++) {
		if (map -> Tile [i].Tile == tile) {
		
			GetMapXY (map, i, int x, int y);
			
			cnt ++;
			sum += sqrtf (powf (x, 2) + powf (y, 2));
		}
	}
	
	return sum / (float) cnt;
}
