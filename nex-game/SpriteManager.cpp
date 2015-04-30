/*
*/

#include "stdafx.h"

#include "SpriteManager.h"
#include "Sprite.h"


SpriteManager::SpriteManager()
{
	//
}

void SpriteManager::AddSprite(Sprite* sprite)
{
	spriteSet_.push_back(sprite);
}

Sprite* SpriteManager::getSprite(int index)
{
	return spriteSet_.at(index);
}
