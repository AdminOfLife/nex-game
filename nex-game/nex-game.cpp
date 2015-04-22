/*
NEXER (nex-game)
Uses SR3 - Southclaw's Retro Rendering Rapter!
*/
#include "stdafx.h"

#include "BitmapLoader.h"
#include "Render.h"
#include "Sprite.h"
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
	Render * render = new Render();
	Game * game = new Game();

	game->AddSprite(&Sprite("charmap.bmp",	16, 1538,	0, GUI, 0));
	game->AddSprite(&Sprite("wall.bmp",		16, 16,		0, MAP, 1));
	game->AddSprite(&Sprite("floor.bmp",	16, 16,		0, MAP, 0));

	Level * level = new Level(game, "http://en.wikipedia.org/wiki/Main_Page");
	Screen * screen = new Screen(render, game, level);

	// Initialisation
	game->Splash(render);

	// Keep this app running until we're told to stop
	MSG msg;

	// Enter main loop
	while (game->GameState != GAME_STATE_END)
	{
		screen->Update(render, game);
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