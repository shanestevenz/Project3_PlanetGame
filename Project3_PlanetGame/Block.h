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
	bool placed;
	virtual int eventHandler(const df::Event* p_e);
	virtual void hit(const df::EventCollision* p_c);
	void setPlaced(bool isPlaced);

};