
#include "Asteroid.h"
#include "EventOut.h"
#include "Explosion.h"
#include <LogManager.h>
#include "ExplosionEvent.h"

Asteroid::Asteroid()
{
	

	// initiallize the random index
	//(left screen--1 , top screen--2, right screen--3, bottom screen--4 )
	randomIndex = rand() % 4 + 1;

	// set sprite
	setSprite("asteroid");

	// set object type
	setType("Asteroid");

	registerInterest(EXPLOSION_EVENT);
	double xVel = 0.2f;
	double yVel = .08f;

	// set the horizontal speed according to index
	// if left screen--1, move 1 space right every 4 frame
	if (randomIndex == 1) setVelocity(df::Vector(xVel, 0));

	// if top screen--2, move 1 space down every 4 frame
	if (randomIndex == 2) setVelocity(df::Vector(0, yVel));

	// if right screen--3, move 1 space left every 4 frame
	if (randomIndex == 3) setVelocity(df::Vector(-xVel, 0));

	// if bottom screen--4, move 1 space up every 4 frame
	if (randomIndex == 4) setVelocity(df::Vector(0, -yVel));

	// spawn the Asteroid randomly at a start location
	moveToStart();

}

Asteroid::~Asteroid()
{

	// Create an explosion.
	Explosion* p_explosion = new Explosion;
	p_explosion->setPosition(this->getPosition());

}

int Asteroid::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::OUT_EVENT) {
		out();
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

			WM.markForDelete(this);

			//new Asteroid;
			LM.writeLog("Asteroid destroyed by explosion");
		}


	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Asteroid::out()
{
	if (getPosition().getX() >= 0 || getPosition().getX() >= 100)
		return;
	// Spawn new Saucer to make the game get harder.
	moveToStart();

	//new Asteroid;
}

void Asteroid::hit(const df::EventCollision* p_c)
{
	if ((p_c->getObject1()->getType() == "Asteroid") &&
		(p_c->getObject2()->getType() == "Asteroid")) {

		LM.writeLog("Removing Asteroid");

		//Explosion* p_explosion = new Explosion;
		//p_explosion->setPosition(this->getPosition());

		WM.markForDelete(this);

		//new Asteroid;
	}

	if ((p_c->getObject1()->getType() == "BigLad") ||
		(p_c->getObject2()->getType() == "BigLad")) {

		LM.writeLog("Removing Asteroid, hit by big lad");

		//Explosion* p_explosion = new Explosion;
		//p_explosion->setPosition(this->getPosition());

		WM.markForDelete(this);

		//new Asteroid;
	}

	// Play "explode" sound.
	//df::Sound* p_sound = RM.getSound("explode");
	//p_sound->play();

}

void Asteroid::moveToStart()
{
	df::Vector temp_pos;
	// get the world boundary
	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	if (randomIndex == 1) { 	// if left screen--1
	
		temp_pos.setX(-3); 	// x is off left side of window

		temp_pos.setY(10 + rand() %  (int)(((world_vert - 10) + 1) - 10)  ); // y is in vertical range.


		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() + 3);
			temp_pos.setX(temp_pos.getX() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}
		WM.moveObject(this, temp_pos);


	}
	else if (randomIndex == 2) {// if top screen--2
	
		temp_pos.setX(10 + rand() % (int)(((world_horiz - 10) + 1) - 10) );	// x is in vertical range

	
		temp_pos.setY(-3);	// y is off top of window


		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() - 3);
			temp_pos.setX(temp_pos.getX() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}
		WM.moveObject(this, temp_pos);


	}

	
	else if (randomIndex == 3) { // if right screen--3
		
		temp_pos.setX(world_horiz + 3); 	// x is off left side of window

		temp_pos.setY(10 + rand() % (int)(((world_vert - 10) + 1) - 10)); // y is in vertical range.


		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() - 3);
			temp_pos.setX(temp_pos.getX() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}
		WM.moveObject(this, temp_pos);
	}

	
	else if (randomIndex == 4) {// if bottom screen--4
		temp_pos.setX(10 + rand() % (int)(((world_horiz - 10) + 1) - 10));	// x is in vertical range


		temp_pos.setY(world_vert + 3);	// y is off top of window


		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() + 3);
			temp_pos.setX(temp_pos.getX() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}
		WM.moveObject(this, temp_pos);


	}


}
