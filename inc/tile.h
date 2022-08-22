#ifndef TILE_H
	#define TILE_H
	
	#include <stdlib.h>
	#include <stdint.h>
	
	typedef uint16_t tile_t;

	#define TILE_NULL	000000

	#define TILE_ROAD	000001

	#define TILE_DIRT	000010
	#define TILE_ROCK	000020
	#define TILE_TREE	000030
	#define TILE_GRASS	000040
	#define TILE_WATER	000050
	
	
	#define TILE_SRC_ELE_S	000100
	#define TILE_SRC_ELE_M	000101
	#define TILE_SRC_ELE_L	000102
	
	#define TILE_SRC_WAT	000110
	#define TILE_SRC_WAT_S	000110
	#define TILE_SRC_WAT_M	000111
	#define TILE_SRC_WAT_L	000112
	
	#define TILE_SRC_POL	000120
	#define TILE_SRC_POL_S	000120
	#define TILE_SRC_POL_M	000121
	#define TILE_SRC_POL_L	000122
#endif
