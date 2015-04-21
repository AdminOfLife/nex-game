#pragma once

#include "Sprite.h"
#include "Tile.h"

class Map
{
public:
	Map(Render render);
	~Map();
	void Update(Render);

private:
	Sprite mapSprites[2];
	Tile tileMap[20 * 15];
};