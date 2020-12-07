#include "Block.h"
#include "Explosion.h"
#include <LogManager.h>
#include <WorldManager.h>
#include <ResourceManager.h>
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

		// if the any of the blick has durability of one, change the color to red
		if (durability == 1) {
			RM.getSprite("block")->setColor(df::RED);
			RM.getSprite("explosion")->setColor(df::YELLOW);
		}

		if (durability <= 0) //Block broke
		{
			WM.markForDelete(this);

			// Create an explosion.
			Explosion* p_explosion = new Explosion;
			p_explosion->setPosition(this->getPosition());

			return;
		}

	}


}
