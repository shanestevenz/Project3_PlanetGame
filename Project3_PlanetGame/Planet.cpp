#include "Planet.h"
#include "Gameover.h"
#include <EventOut.h>
#include <WorldManager.h>
#include <EventView.h>
#include <DisplayManager.h>
#include <LogManager.h>
#include <EventStep.h>
#include "ChangeHealthEvent.h"
#include "BigLad.h"


Planet::Planet()
{

	setSprite("planet");

	// set object type
	setType("Planet");

	//p_blockplacer = new BlockPlacer; //better to put this in gamestart

	// Player controls hero, so register for input events.
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);

	// Need to update rate control each step.
	registerInterest(df::STEP_EVENT);
	registerInterest(HEALTH_EVENT);

	df::Vector p(WM.getBoundary().getHorizontal()/2 , WM.getBoundary().getVertical()/2 );
	//df::Vector p(10, 4);
	setPosition(p);
	health = 100;
}



int Planet::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	if (p_e->getType() == HEALTH_EVENT) {
		const ChangeHealthEvent* p_health_event =
			dynamic_cast <const ChangeHealthEvent*> (p_e);
		
		LM.writeLog("Planet: HEALING for 25");

		health += p_health_event->healthAmount;

		df::EventView ev3("Health", p_health_event->healthAmount, true); //update UI
		WM.onEvent(&ev3);

		//play sound?? healing noise

		return 1;
	}

}

void Planet::hit(const df::EventCollision* p_c)
{
	//decerese health

	if (((p_c->getObject2()->getType()) == "Asteroid") || ((p_c->getObject1()->getType()) == "Asteroid"))
	{
		if (((p_c->getObject1()->getType()) == "Asteroid"))
		{
			WM.markForDelete(p_c->getObject1());
		}
		else
			WM.markForDelete(p_c->getObject2()); //delete Asteroid


		//decerese health
		health -= 10;
		df::EventView ev2("Health", -10, true); //update UI
		WM.onEvent(&ev2);



		if (health <= 0) //PLANET died
		{
			WM.markForDelete(this);

			return;
		}

	}

	if (((p_c->getObject2()->getType()) == "BigLad") || ((p_c->getObject1()->getType()) == "BigLad"))
	{
		if (((p_c->getObject1()->getType()) == "BigLad"))
		{
			WM.markForDelete(p_c->getObject1());
		}
		else
			WM.markForDelete(p_c->getObject2()); //delete Asteroid


		const BigLad* p_BigLad;

		if (((p_c->getObject1()->getType()) == "BigLad"))
		{
			p_BigLad = dynamic_cast <const BigLad*> (p_c->getObject1());
		}
		else
			p_BigLad = dynamic_cast <const BigLad*> (p_c->getObject2());




		LM.writeLog("Planet was hit by big lad");

		//decerese health
		health -= p_BigLad->health;
		df::EventView ev2("Health", -p_BigLad->health, true); //update UI
		WM.onEvent(&ev2);



		if (health <= 0) //PLANET died
		{
			WM.markForDelete(this);

			return;
		}

	}


}
void Planet::step()
{
	//nothing atm
}

void Planet::kbd(const df::EventKeyboard* p_keyboard_event)
{
	switch (p_keyboard_event->getKey()) { //for future features
	case df::Keyboard::Q:        // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.markForDelete(this);
		break;
	default: // Key not handled.
		return;
	};

}



Planet::~Planet()
{

	// Shake screen (severity 20 pixels x&y, duration 10 frames).
	DM.shake(20, 20, 10);

	// Play "big explosion" sound.
	df::Sound* p_sound = RM.getSound("big explosion");
	p_sound->play();

	// Create GameOver object.
	new GameOver;
}