#pragma once
#include "Object.h"
#include <EventCollision.h>
#include <Vector.h>
class Block : public df::Object 
{
public:
	Block(); 
	Block(df::Vector);
	~Block();
	int durability;

	int eventHandler(const df::Event* p_e);
	void hit(const df::EventCollision* p_c);


};