#pragma once
#include "Object.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "Explosion.h"
#include "ResourceManager.h"
#include "Asteroid.h"
class BigLad : public Asteroid
{
public:
	BigLad();
	~BigLad();

	void hit(const df::EventCollision* p_c);
	int eventHandler(const df::Event* p_e);
	int health;
};

