#pragma once
#include "Block.h"
class HeavyBlock :public Block
{

public:
	HeavyBlock();
	HeavyBlock(df::Vector pos);
	~HeavyBlock();
	//void hit(const df::EventCollision* p_c);


};

