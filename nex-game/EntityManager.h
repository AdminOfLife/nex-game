#pragma once
#include "stdafx.h"

class Render;
class Entity;
class Sprite;

class EntityManager
{
public:
	EntityManager();
	
	Entity* CreateEntity(Sprite* sprite, POINT position, double angle, double velX, double velY, int ttl = -1);
	void DestroyEntity(Entity* entity);
	void update();
	void draw(Render* render);
	void getEntitySet(set<Entity*> entitySet);

private:
	set<Entity*> entitySet_;
};