#pragma once
#include "Object.h"
#include "EventMouse.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Block.h"

class BlockPlacer : public df::Object {
public:
	BlockPlacer();
	int eventHandler(const df::Event* p_e);
	int draw(void);
	void mouse(const df::EventMouse* p_mouse_event);
	int numberOfBlocks;
	void step();
};