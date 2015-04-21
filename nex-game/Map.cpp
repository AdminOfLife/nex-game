#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <cmath>

#include "Render.h"
#include "Map.h"
#include "Sprite.h"
#include "Tile.h"


Map::Map(Render render)//, Level level)
{
	// get tilemap from level
	// temp tile map:

	// Load sprites
	mapSprites[0] = Sprite("wall.bmp", 16, 16, 0, MAP);
	mapSprites[1] = Sprite("floor.bmp", 16, 16, 0, MAP);

	// Place sprites into tiles
	int x = 0;
	int y = 0;
	for (int i = 0; i < 20 * 15; ++i)
	{
		tileMap[i] = Tile(x, y, mapSprites[rand() % 2]);
		x++;
		if (x == 20)
		{
			x = 0;
			y++;
		}
	}
}

Map::~Map()
{

}

void Map::Update(Render render)
{
	for (int i = 0; i < 20 * 15; ++i)
	{
		tileMap[i].Draw(render);
	}
}