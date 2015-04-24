/*
*/

#include "stdafx.h"

#include "Character.h"
#include "Sprite.h"


Character::Character()
{
	//
}

Character::Character(Sprite* spr, int spawnx, int spawny)
{
	sprite = spr;
	posX = spawnx;
	posY = spawny;
}

void Character::Move(float direction, float speed)
{
	posX += round(speed * sin(-direction));
	posY += round(speed * cos(-direction));
}

void Character::Draw(Render* render)
{
	sprite->DrawAt(render, posX, posY);
}

void Character::GetPos(POINT* point)
{
	point->x = posX;
	point->y = posY;
}