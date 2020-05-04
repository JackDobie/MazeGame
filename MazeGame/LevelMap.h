#pragma once

#define MAP_HEIGHT	35
#define MAP_WIDTH	36
#define TILE_WIDTH	1
#define TILE_HEIGHT	1

class LevelMap
{
private:
	int** mMap;
public:
	LevelMap();
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);
};