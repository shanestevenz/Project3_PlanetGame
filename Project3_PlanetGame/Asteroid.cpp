
#include "Asteroid.h"
#include "EventOut.h"
#include "Explosion.h"
#include <LogManager.h>


Asteroid::Asteroid()
{
	// initiallize the random index
	//(left screen--1 , top screen--2, right screen--3, bottom screen--4 )
	randomIndex = rand() % 4 + 1;

	// set sprite
	setSprite("asteroid");

	// set object type
	setType("Asteroid");

	// set the horizontal speed according to index
	// if left screen--1, move 1 space right every 4 frame
	if (randomIndex == 1) setVelocity(df::Vector(0.25, 0));

	// if top screen--2, move 1 space down every 4 frame
	if (randomIndex == 2) setVelocity(df::Vector(0, 0.1));

	// if right screen--3, move 1 space left every 4 frame
	if (randomIndex == 3) setVelocity(df::Vector(-0.25, 0));

	// if bottom screen--4, move 1 space up every 4 frame
	if (randomIndex == 4) setVelocity(df::Vector(0, -0.1));

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

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

}

void Asteroid::out()
{
	if (getPosition().getX() >= 0)
		return;
	// Spawn new Saucer to make the game get harder.
	moveToStart();

	new Asteroid;
}

void Asteroid::hit(const df::EventCollision* p_c)
{
	if ((p_c->getObject1()->getType() == "Asteroid") &&
		(p_c->getObject2()->getType() == "Asteroid")) {

		LM.writeLog("Removing Asteroid");
		WM.markForDelete(this);
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

	// if left screen--1
	if (randomIndex == 1) {
		// x is off left side of window
		temp_pos.setX(0 - rand() % (int)world_horiz + 4.0f);

		// y is in vertical range.
		temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

		// If collision, move left slightly until empty space.
		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}

		WM.moveObject(this, temp_pos);
	}

	// if top screen--2
	if (randomIndex == 2) {
		// x is in vertical range
		temp_pos.setX(rand() % (int)(world_horiz - 4) + 4.0f);

		// y is off top of window
		temp_pos.setY(0 - rand() % (int)world_vert + 2.0f);

		// If collision, move up slightly until empty space.
		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() - 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}

		WM.moveObject(this, temp_pos);
	}

	// if right screen--3
	if (randomIndex == 3) {
		// x is off right side of window
		temp_pos.setX(world_horiz + rand() % (int)world_horiz + 4.0f);

		// y is in vertical range.
		temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

		// If collision, move right slightly until empty space.
		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setX(temp_pos.getX() + 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}

		WM.moveObject(this, temp_pos);
	}

	// if bottom screen--4
	if (randomIndex == 4) {
		// x is in horizontal range
		temp_pos.setX(rand() % (int)(world_horiz - 4) + 4.0f);

		// y is down off window
		temp_pos.setY(world_vert + rand() % (int)world_vert + 2.0f);

		// If collision, move down slightly until empty space.
		df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
		while (!collision_list.isEmpty()) {
			temp_pos.setY(temp_pos.getY() + 1);
			collision_list = WM.getCollisions(this, temp_pos);
		}

		WM.moveObject(this, temp_pos);
	}


}
