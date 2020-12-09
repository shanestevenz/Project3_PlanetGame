#pragma once
#include "Object.h"
#include <EventCollision.h>
#include <EventKeyboard.h>
#include "BlockPlacer.h"
#include "ResourceManager.h"

class Planet : public df::Object 
{

private:
	int health;
	void step();
	//BlockPlacer* p_blockplacer;
	void kbd(const df::EventKeyboard* p_keyboard_event);

public:
	Planet();
	~Planet();
	int eventHandler(const df::Event* p_e);
	void hit(const df::EventCollision* p_c);
};

