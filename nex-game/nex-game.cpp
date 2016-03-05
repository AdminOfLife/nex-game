/*
NEXER (nex-game)
Uses SR3 - Southclaw's Retro Rendering Rapter!
*/
#include "stdafx.h"

#include "Logger.h"
#include "BitmapLoader.h"
#include "Render.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Game.h"
#include "Tile.h"
#include "TileMap.h"
#include "Level.h"
using namespace std;


int main(int argc, char* argv[])
{
	//SetConsoleTitle(L"NEXER - Explore the internet!");
	SetConsoleTitle(L"Southclaw's 2D Retro Rendering Rapter!");

	log_init(DEBUG_NONE);

	logs(DEBUG_CORE) << "Southclaw's 2D Retro Rendering Rapter Engine Initialising";

	// Construction
	logs(DEBUG_CORE) << "Running core constructors";
	Render* render = new Render();
	SpriteManager* sm = new SpriteManager();
	Game* game = new Game(render, sm);

	Sprite* tmp;

	logs(DEBUG_CORE) << "Registering Sprites";
	sm->AddSprite(tmp = new Sprite("wall.bmp", 16, 16, MAP, SQUARE));
	sm->AddSprite(tmp = new Sprite("floor.bmp",		16, 16, MAP, NOCOLL));
	sm->AddSprite(tmp = new Sprite("chr.bmp",		16, 16, CHR, CIRCLE));
	sm->AddSprite(tmp = new Sprite("blocker.bmp",	16, 16, MAP, SQUARE));
	sm->AddSprite(tmp = new Sprite("laser.bmp",		16, 16, ENT, NOCOLL));

//	Screen* screen = new Screen(render, game, game->GameLevel);

	// Initialisation
	logs(DEBUG_CORE) << "Running game initialisation";
	game->init();

	// Enter main loop
	while (game->GameState != GAME_STATE_END)
	{
		logs(DEBUG_LOOPS) << "GAME LOOP ITERATION";
		game->update(render);
		render->update();
	}

	return 0;
}
