#pragma once
#include "stdafx.h"

class Sprite;
class Render;

class Entity
{
public:
	Entity(Sprite* sprite, POINT position, double angle, double velx, double vely, int ttl = -1);
	~Entity();

	void update();
	void draw(Render* render);

	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	void setPos(POINT position);
	void getPos(POINT& position);
	void setAngle(double angle);
	double getAngle();
	void setVelocity(double x, double y);
	void getVelocity(double& x, double& y);
	unsigned long getTimeCreated();
	unsigned long getTimeToLive();


private:
	Sprite* sprite_;
	POINT position_;
	double angle_;
	double velX_;
	double velY_;
	unsigned long timeCreated_;
	unsigned long timeToLive_;
};