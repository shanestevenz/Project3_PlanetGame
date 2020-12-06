#pragma once
#include "Object.h"
#include <EventCollision.h>

class Planet : public df::Object 
{

private:
	int health = 2;
	void step();


public:
	Planet();
	~Planet();
	int eventHandler(const df::Event* p_e);
	void hit(const df::EventCollision* p_c);
};

