/*
*/

#include "stdafx.h"

#include "Logger.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Sprite.h"


EntityManager::EntityManager()
{
	//
}

Entity* EntityManager::CreateEntity(Sprite* sprite, POINT position, double angle, double velX, double velY, int ttl)
{
	Entity* entity = new Entity(sprite, position, angle, velX, velY, ttl);
	entitySet_.insert(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	entitySet_.erase(entity);
	delete entity;
}

void EntityManager::getEntitySet(set<Entity*> entitySet)
{  
	entitySet = entitySet_;
}

void EntityManager::update()
{
	logf(DEBUG_CORE, "entity update entry for %x", this);
	set<Entity*>::iterator e;

	for (e = entitySet_.begin(); e != entitySet_.end();)
	{
		logf(DEBUG_LOOPS, "looping entity set");
		if ((*e)->getTimeToLive() != -1)
		{
			logf(DEBUG_LOOPS, "entity timeToLive is %d", (*e)->getTimeToLive());
			if (GetTickCount() - (*e)->getTimeCreated() > (*e)->getTimeToLive())
			{
				DestroyEntity((*e++));
				continue;
			}
		}

		(*e)->update();

		++e;
	}
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
	// lazy mathod, 4 loops:
	for (auto e : entitySet_)
	{
		if (e->getSprite()->getType() == MAP)
			e->draw(render);
	}

	for (auto e : entitySet_)
	{
		if (e->getSprite()->getType() == ENT)
			e->draw(render);
	}

	for (auto e : entitySet_)
	{
		if (e->getSprite()->getType() == CHR)
			e->draw(render);
	}

	for (auto e : entitySet_)
	{
		if (e->getSprite()->getType() == GUI)
			e->draw(render);
	}
}

bool EntityManager::isColliding(Entity* entity)
{
	for (auto e : entitySet_)
	{
		if (entity == e)
			continue;

		if (entity->isCollidingWith(e))
			return true;
	}

	return false;
}
