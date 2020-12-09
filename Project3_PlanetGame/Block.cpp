#include "Block.h"
#include "Explosion.h"
#include <LogManager.h>
#include <WorldManager.h>
#include <ResourceManager.h>
#include <Color.h>
#include "Points.h"
#include <EventView.h>
#include <EventOut.h>
#include "BigLad.h"

Block::Block()
{

	setSprite("block");

	// set object type
	setType("Block");

	durability = 5;
	setPlaced(false);
	LM.writeLog("Block placed");
}

Block::Block(df::Vector pos)
{

	setSprite("block");

	// set object type
	setType("Block");

	durability = 5;
	setPosition(pos);
	setPlaced(false);
	LM.writeLog("Block placed");
}

Block::~Block()
{
	
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

	if (p_e->getType() == df::OUT_EVENT) {
		WM.markForDelete(this);
		return 1;
	}

	return 0;
}

 void Block::hit(const df::EventCollision* p_c)
{


	if (!placed)
	{
		return;
	}


	if (((p_c->getObject2()->getType()) == "Asteroid") || ((p_c->getObject1()->getType()) == "Asteroid"))
	{
		if (((p_c->getObject1()->getType()) == "Asteroid"))
		{
			WM.markForDelete(p_c->getObject1());
		}
		else
			WM.markForDelete(p_c->getObject2()); //delete Asteroid

		df::EventView ev(MONEY_STRING, +10, true); //give Money
		WM.onEvent(&ev);
		//decerese health
		durability--;
		LM.writeLog("Block hit by asteroid");

		// if the any of the blick has durability of one, change the color to red
		if (durability == 1) {
			
			//getAnimation().getSprite()->setColor(df::RED);
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


	if (((p_c->getObject2()->getType()) == "BigLad") || ((p_c->getObject1()->getType()) == "BigLad"))
	{
		const BigLad* p_biglad;

		if (((p_c->getObject1()->getType()) == "BigLad"))
		{
			p_biglad = dynamic_cast <const BigLad*> (p_c->getObject1());
		}
		else
			p_biglad = dynamic_cast <const BigLad*> (p_c->getObject2());


		

		df::EventView ev(MONEY_STRING, +10, true); //give Money
		WM.onEvent(&ev);
		//decerese health

		durability-= p_biglad->health;


		LM.writeLog("Block hit by asteroid");

		// if the any of the blick has durability of one, change the color to red
		if (durability == 1) {

			//getAnimation().getSprite()->setColor(df::RED);
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

void Block::setPlaced(bool isPlaced)
{
	placed = isPlaced;
}
