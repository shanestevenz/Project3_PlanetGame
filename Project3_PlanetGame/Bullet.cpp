
#pragma region Includes



//managers
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"


//objects
#include "Bullet.h"
#include "Asteroid.h"
//events
#include "EventOut.h"
#include "Points.h"
#include <EventView.h>
#pragma endregion

Bullet::Bullet(df::Vector start_pos)
{
	setSprite("bullet"); //link to sprite
	setSolidness(df::SOFT); //sets as soft
	setType("Bullet"); //set type as bullet

	df::Vector p(start_pos.getX() + 3, start_pos.getY());//start pos
	setPosition(p);
	setSpeed(1);//moves 1 space per gameloop

}

Bullet::~Bullet()
{
}

// Eventhandler: Return 1 if handled. else 0 if ignored
int Bullet::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}


	return 0; //event ignoredd
}


void Bullet::out() { //when bullet leaves bounds
	WM.markForDelete(this);
}

//When the bullet hits a suacer
void Bullet::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Asteroid") ||
		(p_collision_event->getObject2()->getType() == "Asteroid")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
		new Asteroid;
		df::EventView ev(MONEY_STRING, +5, true); //give Money
		WM.onEvent(&ev);
	}
}