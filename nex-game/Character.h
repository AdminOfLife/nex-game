#pragma once
#include "stdafx.h"

#include "Sprite.h"


class Character
{
public:
	Character();
	Character(Sprite* spr, int spawnx, int spawny);

	void Move(float direction, float speed);
	void Draw(Render* render);
	void GetPos(POINT* point);

private:
	Sprite* sprite;
	int posY;
	int posX;
};