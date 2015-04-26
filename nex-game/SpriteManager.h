#pragma once
#include "stdafx.h"

class Sprite;

class SpriteManager
{
public:
	SpriteManager();
	void AddSprite(Sprite* sprite);
	Sprite* GetSprite(int index);

private:
	vector<Sprite*> spriteSet_;
};