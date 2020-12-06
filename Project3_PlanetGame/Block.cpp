#include "Block.h"
#include "Explosion.h"
#include <LogManager.h>
#include <WorldManager.h>
#include <Color.h>

Block::Block()
{

	setSprite("block");

	// set object type
	setType("Block");

	durability = 5;
	LM.writeLog("Block placed");
}

Block::Block(df::Vector pos)
{

	setSprite("block");

	// set object type
	setType("Block");

	durability = 5;
	setPosition(pos);

	LM.writeLog("Block placed");
}

Block::~Block()
{
	Explosion* p_explosion = new Explosion(df::YELLOW);
	p_explosion->setPosition(this->getPosition());  
	LM.writeLog("Block Destroyed");
}

int Block::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

void Block::hit(const df::EventCollision* p_c)
{
	if (((p_c->getObject2()->getType()) == "Asteroid") || ((p_c->getObject1()->getType()) == "Asteroid"))
	{
		if (((p_c->getObject1()->getType()) == "Asteroid"))
		{
			WM.markForDelete(p_c->getObject1());
		}
		else
			WM.markForDelete(p_c->getObject2()); //delete Asteroid


		//decerese health
		durability--;
		LM.writeLog("Block hit by asteroid");
		if (durability <= 0) //Block broke
		{
			WM.markForDelete(this);

			return;
		}

	}


}
