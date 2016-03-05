/*
*/

#include "stdafx.h"

#include "Logger.h"
#include "Character.h"
#include "Render.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"


Character::Character(EntityManager* em, SpriteManager* sm, Sprite* sprite, POINT position, double angle)
{
	logc(DEBUG_CORE, "Created character");

	entity_ = em->CreateEntity(sprite, position, angle, 0.0, 0.0);
	entityManager_ = em;
	spriteManager_ = sm;
	logf(DEBUG_CORE_DEEP, "ent adr: %x entmgr adr: %x sprmgr adr: %x", entity_, entityManager_, spriteManager_);
}

Character::~Character()
{
	logc(DEBUG_CORE, "Destroyed character");
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
	logs(DEBUG_INTERFACE) << "fireWeapon called";

	POINT position;
	double angle;
	entity_->getPos(position);
	angle = entity_->getAngle(); 

	logs(DEBUG_INTERFACE_DEEP)
		<< "fireWeapon position: " << position.x << "," << position.y
		<< "angle: " << angle << ".";

	entityManager_->CreateEntity(spriteManager_->getSprite(4), position, angle, 10 * sin(-angle), 10 * cos(-angle), 500);
}



void Character::setPos(POINT position)
{
	logf(DEBUG_INTERFACE, "setPos to: %f, %f", position.x, position.y);
	logs(DEBUG_INTERFACE) << "setPos to: " << position.x << ", " << position.y << "";
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
