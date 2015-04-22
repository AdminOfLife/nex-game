#pragma once
#include "stdafx.h"

#include "Game.h"
#include "Level.h"
#include "Tile.h"
#include "Sprite.h"


class Screen
{
public:
	Screen(Render * render, Game * game, Level * level);
	~Screen();
	void Update(Render * render, Game * game);

private:
	TileMap tileMap;
};