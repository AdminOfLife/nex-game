/*
NEXER (nex-game)
Uses SR3 - Southclaw's Retro Rendering Rapter!
*/
#include "stdafx.h"

#include "BitmapLoader.h"
#include "Render.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Game.h"
#include "Tile.h"
#include "TileMap.h"
#include "Level.h"
#include "Screen.h"
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	//SetConsoleTitle(L"NEXER - Explore the internet!");
	SetConsoleTitle(L"Southclaw's 2D Retro Rendering Rapter!");

	// Construction
	Render* render = new Render();
	SpriteManager* sm = new SpriteManager();
	Game* game = new Game(render, sm);

	Sprite* tmp;

	sm->AddSprite(tmp = new Sprite("wall.bmp",		16, 16, 0, MAP, SQUARE));
	sm->AddSprite(tmp = new Sprite("floor.bmp",		16, 16, 0, MAP, NOCOLL));
	sm->AddSprite(tmp = new Sprite("chr.bmp",		16, 16, 0, CHR, CIRCLE));
	sm->AddSprite(tmp = new Sprite("blocker.bmp",	16, 16, 0, MAP, SQUARE));
	sm->AddSprite(tmp = new Sprite("laser.bmp",		16, 16, 0, ENT, NOCOLL));

//	Screen* screen = new Screen(render, game, game->GameLevel);

	// Initialisation
	game->Init();

	// Enter main loop
	while (game->GameState != GAME_STATE_END)
	{
//		screen->Update(render, game);
		game->Update(render);
		render->Update();
	}

	return 0;
}
/*
int randrange(int min, int max)
{
	return min + (rand() % (int)(max - min + 1));
}

void test(Render render)
{
	int x = 0, y = 0;
	COLORREF c;

	for (int i = 0; i < 100; i++)
	{
		x = randrange(0, SCREEN_SIZE_X);
		y = randrange(0, SCREEN_SIZE_Y);
		c = RGB(randrange(0, 255), randrange(0, 255), randrange(0, 255));
		render.SetFrameBufferPixel(x, y, c);
	}
}

*/