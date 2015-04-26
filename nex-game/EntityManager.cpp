/*
*/

#include "stdafx.h"

#include "EntityManager.h"
#include "Entity.h"
#include "Sprite.h"


EntityManager::EntityManager()
{
	//
}

Entity* EntityManager::CreateEntity(Sprite* sprite, POINT position, double angle, double velX, double velY, int ttl)
{
	Entity* entity = new Entity(sprite, position, angle, velX, velY);
	entitySet_.insert(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	entitySet_.erase(entity);
	entity->~Entity();
	delete entity;
}

void EntityManager::getEntitySet(set<Entity*> entitySet)
{
	entitySet = entitySet_;
}

void EntityManager::update()
{
	// update all entites
}

void EntityManager::draw(Render* render)
{
	// draw all entites in this order:
	/*
	MAP, // map tiles
	ENT,  // entities
	CHR, // characters
	GUI // ui
	*/
}
