#include "BigLad.h"

#include "EventOut.h"
#include "Explosion.h"
#include <LogManager.h>
#include "ExplosionEvent.h"
#include "Block.h"
#include <DisplayManager.h>
#include "EventCollision.h"
#include "HeavyBlock.h"
#include "Points.h"
#include <EventView.h>
BigLad::BigLad()
{


	// initiallize the random index
	
	randomIndex = rand() % 2 + 1;

	// set sprite
	setSprite("biglad");

	// set object type
	setType("BigLad");

	registerInterest(EXPLOSION_EVENT);
	double xVel = 0.15f;
	if (randomIndex == 1) setVelocity(df::Vector(xVel, 0));

	// if right screen--3, move 1 space left every 4 frame
	if (randomIndex == 2) setVelocity(df::Vector(-xVel, 0));


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

	if (health >= 0) //was destroyed by player, not system
	{
		df::EventView ev(MONEY_STRING, +100, true); //give Money
		WM.onEvent(&ev);
	}
	
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


	if ((p_c->getObject1()->getType() == "Bullet") || (p_c->getObject2()->getType() == "Bullet"))
	{

		

		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(p_c->getObject1()->getPosition());

		//LM.writeLog("Big lad hit the planet");
		health--;

	}

	if (health <= 0 )
	{
		WM.markForDelete(this);
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




void BigLad::moveToStart()
{

	LM.writeLog("BIG LAD MOVE TO START %d", randomIndex);
	df::Vector temp_pos;
	// get the world boundary
	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	if (randomIndex == 1) { 	// if left screen--1

		temp_pos.setX(-3); 	// x is off left side of window

		temp_pos.setY(20 + rand() % (int)(((world_vert - 20) + 1) - 20)); // y is in vertical range.


		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() + 3);
			temp_pos.setX(temp_pos.getX() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}
		WM.moveObject(this, temp_pos);


	}
	

	else if (randomIndex == 2) { // if right screen--3

		temp_pos.setX(world_horiz + 3); 	// x is off left side of window

		temp_pos.setY(20 + rand() % (int)(((world_vert - 20) + 1) - 20)); // y is in vertical range.


		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() - 3);
			temp_pos.setX(temp_pos.getX() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}
		WM.moveObject(this, temp_pos);
	}



}

