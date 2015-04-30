/*
*/

#include "stdafx.h"

#include "Character.h"
#include "Render.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"


Character::Character(EntityManager* em, SpriteManager* sm, Sprite* sprite, POINT position, double angle)
{
	entity_ = em->CreateEntity(sprite, position, angle, 0.0, 0.0);
	entityManager_ = em;
	spriteManager_ = sm;
}

Character::~Character()
{
	entityManager_->DestroyEntity(entity_);
}

void Character::update()
{
	entity_->update();
}

void Character::draw(Render* render)
{
	entity_->draw(render);
}

Entity* Character::getEntity()
{
	return entity_;
}

void Character::fireWeapon()
{
	POINT position;
	double angle;
	entity_->getPos(position);
	angle = entity_->getAngle();

	entityManager_->CreateEntity(spriteManager_->getSprite(4), position, angle, 10 * sin(-angle), 10 * cos(-angle), 500);
}



void Character::setPos(POINT position)
{
	entity_->setPos(position);
}

void Character::getPos(POINT& position)
{
	entity_->getPos(position);
}

void Character::setAngle(double angle)
{
	entity_->setAngle(angle);
}

double Character::getAngle()
{
	return entity_->getAngle();
}

void Character::setVelocity(double x, double y)
{
	entity_->setVelocity(x, y);
}

void Character::getVelocity(double& x, double& y)
{
	entity_->getVelocity(x, y);
}
