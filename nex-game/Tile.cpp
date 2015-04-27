/*
Tile
A [Tile] consists of a sprite and a tile position.
A tile position is an x,y between [(0,0),(20,15)].
*/

#include "stdafx.h"

#include "Sprite.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Tile.h"


Tile::Tile()
{
	//
}

Tile::Tile(EntityManager* em, Sprite* sprite, int x, int y)
{
	entity_ = em->CreateEntity(sprite, { x, y }, 0.0, 0.0, 0.0);

	entityManager_ = em;
	gridX_ = x / 16;
	gridY_ = y / 16;
}

Tile::~Tile()
{
	// nothing to delete
}

void Tile::draw(Render* render)
{
	POINT pos;
	entity_->getPos(pos);
	entity_->draw(render);
}

Entity* Tile::getEntity()
{
	return entity_;
}

void Tile::getGridPos(int &x, int &y)
{
	x = gridX_;
	y = gridY_;
}
