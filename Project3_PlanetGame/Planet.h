#pragma once
#include "Object.h"
#include <EventCollision.h>
#include "BlockPlacer.h"

class Planet : public df::Object 
{

private:
	int health = 2;
	void step();
	BlockPlacer* p_blockplacer;

public:
	Planet();
	~Planet();
	int eventHandler(const df::Event* p_e);
	void hit(const df::EventCollision* p_c);
};

