#pragma once
#include "Block.h"
class Bomb : public Block
{


public:
	Bomb();
	Bomb(df::Vector pos);
	~Bomb();

	double explosionRange;
	void hit(const df::EventCollision* p_c);

};

