/*
*/

#include "stdafx.h"

#include "Entity.h"
#include "Render.h"
#include "Sprite.h"


Entity::Entity(Sprite* sprite, POINT position, double angle, double velx, double vely, int ttl)
{
	sprite_ = sprite;
	position_ = position;
	angle_ = angle;
	velX_ = velx;
	velY_ = vely;
	timeCreated_ = GetTickCount();
	timeToLive_ = ttl;
	printf("createentity\n");
}

Entity::~Entity()
{
	printf("destroyentity\n");
}

void Entity::update()
{
	if (timeToLive_ != -1)
	{
		if (GetTickCount() - timeCreated_ > timeToLive_)
		{
			delete this;
			return;
		}
	}

	if (position_.x + velX_ - 8 < 0 || position_.x + velX_ + 8 > SCREEN_SIZE_X)
		velX_ = 0;

	if (position_.y + velY_ - 8 < 0 || position_.y + velY_ + 8 > SCREEN_SIZE_Y)
		velY_ = 0;

	// Additional collision checks go here

	/*
	// Get the tile colliding with xy
	Tile tile;
	int tilex, tiley;

	Tile tilemap[20 * 15];
	GameLevel->GetTileMap(GameLevel->GetActiveMap())->GetTiles(tilemap);

	for (int i = 0; i < 20 * 15; ++i) // replace with area based loop for closest 8 tiles
	{
		tile = tilemap[i];

		COLLISION_TYPE tile_coltype = tile.GetSprite()->GetColType();

		if (tile_coltype == NOCOLL)
			continue;

		tile.getPos(tilex, tiley);

		if (tile_coltype == CIRCLE)
		{
			if (sqrt(pow((pos.x + offset.x) - tilex, 2) + pow((pos.y + offset.y) - tiley, 2)) < 8.0)
			{
				offset.x = 0;
				offset.y = 0;
			}
		}
	}
	*/

	position_.x += (int)round(velX_);
	position_.y += (int)round(velY_);
}

void Entity::draw(Render* render)
{
	sprite_->DrawAt(render, position_.x, position_.y, angle_);
}


void Entity::setSprite(Sprite* sprite)
{
	sprite_ = sprite;
}

Sprite* Entity::getSprite()
{
	return sprite_;
}

void Entity::setPos(POINT position)
{
	position_ = position;
}

void Entity::getPos(POINT& position)
{
	position = position_;
}

void Entity::setAngle(double angle)
{
	angle_ = angle;
}

double Entity::getAngle()
{
	return angle_;
}

void Entity::setVelocity(double x, double y)
{
	velX_ = x;
	velY_ = y;
}

void Entity::getVelocity(double& x, double& y)
{
	x = velX_;
	y = velY_;
}

