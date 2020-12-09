#include "BigLad.h"

#include "EventOut.h"
#include "Explosion.h"
#include <LogManager.h>
#include "ExplosionEvent.h"
#include "Block.h"
#include <DisplayManager.h>
#include "EventCollision.h"
#include "HeavyBlock.h"
BigLad::BigLad()
{


	// initiallize the random index
	//(left screen--1 , top screen--2, right screen--3, bottom screen--4 )
	randomIndex = rand() % 2 + 1;

	// set sprite
	setSprite("biglad");

	// set object type
	setType("BigLad");

	registerInterest(EXPLOSION_EVENT);
	double xVel = 0.15f;

	// set the horizontal speed according to index
	// if left screen--1, move 1 space right every 4 frame
	if (randomIndex == 1) setVelocity(df::Vector(xVel, 0));

	// if right screen--3, move 1 space left every 4 frame
	if (randomIndex == 3) setVelocity(df::Vector(-xVel, 0));


	// spawn the Asteroid randomly at a start location
	moveToStart();

	health = 50;
	LM.writeLog("BIG LAD SPAWN");
}

BigLad::~BigLad()
{

	df::addParticles(df::SPARKS, getPosition(), 4, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 1, df::MAGENTA);

}


void BigLad::hit(const df::EventCollision* p_c)
{
	LM.writeLog("BIG LAD hit:  %s on %s", p_c->getObject1()->getType(), p_c->getObject2()->getType());
	if ((p_c->getObject1()->getType() == "Asteroid") ||
		(p_c->getObject2()->getType() == "Asteroid")) 
	{
		
		

		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		LM.writeLog("Big lad hit asteroid");
		health--;

	}

	if ((p_c->getObject1()->getType() == "Block") || (p_c->getObject2()->getType() == "Block"))
	{
		const Block* p_Block;

		if (((p_c->getObject1()->getType()) == "Block"))
		{
			p_Block = dynamic_cast <const Block*> (p_c->getObject1());
		}
		else
			p_Block = dynamic_cast <const Block*> (p_c->getObject2());


		health-= p_Block->durability;

		DM.shake(5,5,5);
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		LM.writeLog("Big lad hit block");
		

	}

	if ((p_c->getObject1()->getType() == "HeavyBlock") || (p_c->getObject2()->getType() == "HeavyBlock"))
	{
		const HeavyBlock* p_Block;

		if (((p_c->getObject1()->getType()) == "HeavyBlock"))
		{
			p_Block = dynamic_cast <const HeavyBlock*> (p_c->getObject1());
		}
		else
			p_Block = dynamic_cast <const HeavyBlock*> (p_c->getObject2());


		health -= p_Block->durability;

		DM.shake(5, 5, 5);
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());
		LM.writeLog("Big lad hit HeavyBlock");


	}



	if ((p_c->getObject1()->getType() == "Planet") || (p_c->getObject2()->getType() == "Planet"))
	{
		
		WM.markForDelete(this);

		DM.shake(5, 5, 5);
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		LM.writeLog("Big lad hit the planet");


	}

}

int BigLad::eventHandler(const df::Event* p_e)
{

	LM.writeLog("BIG LAD event");
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		LM.writeLog("BIG LAD COLLISION event");
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		this->hit(p_collision_event);
		return 1;
	}

	if (p_e->getType() == EXPLOSION_EVENT) {

		const ExplosionEvent* p_explosion_event =
			dynamic_cast <const ExplosionEvent*> (p_e);



		float d = df::distance(getPosition(), p_explosion_event->explosionPos);

		LM.writeLog("Asteroid distance from explosion: %f", d);
		if (d <= p_explosion_event->explosionRange) //within explosion range
		{

			// Delete this Asteroid

			df::addParticles(df::SPARKS, getPosition(), 1, df::BLUE);
			df::addParticles(df::SPARKS, getPosition(), 1, df::YELLOW);

			//WM.markForDelete(this);
			health -= p_explosion_event->explosionDamage;
			LM.writeLog("Big lad Hit by explosion");
		}


	}

	
	return 0;
}
