#pragma once
#include "Object.h"

class BlockPlacer : public df::Object {
public:
	BlockPlacer();
	int eventHandler(const df::Event* p_e);
	int draw(void);
};