#pragma once
#include "stdafx.h"

class Sprite;
class Render;
class Entity;
class EntityManager;

class Tile
{
public:
	Tile();
	Tile(EntityManager* em, Sprite* sprite, int x, int y);
	~Tile();

	void draw(Render* render);
	Entity* getEntity();

	void getGridPos(int &x, int &y);

private:
	Entity* entity_;
	EntityManager* entityManager_;

	// these positions are not screen positions, they are grid refs
	int gridX_; // 0-19
	int gridY_; // 0-14
};
