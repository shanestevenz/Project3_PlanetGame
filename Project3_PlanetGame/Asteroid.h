#pragma once
#include "Object.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "Explosion.h"
#include "ResourceManager.h"


class Asteroid : public df::Object {

public:
	Asteroid();
	~Asteroid();
	int randomIndex;

	int eventHandler(const df::Event* p_e);
	void out();
	void hit(const df::EventCollision* p_c);
	void moveToStart();

};