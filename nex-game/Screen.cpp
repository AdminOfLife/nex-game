/*
Screen
Handles a single map of 20x15 tiles and draws it.
*/
#include "stdafx.h"

#include "Screen.h"
#include "Render.h"
#include "Game.h"
#include "Sprite.h"
#include "Tile.h"
#include "Level.h"


Screen::Screen(Render * render, Game * game, Level * level)
{
	tileMap = level->GetTileMap(level->GetActiveMap());
}

void Screen::Update(Render * render, Game * game)
{

	return;
}
