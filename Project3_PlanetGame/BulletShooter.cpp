#include "BulletShooter.h"
#include <WorldManager.h>
#include <EventStep.h>
#include "Bullet.h"
#include <LogManager.h>



BulletShooter::BulletShooter()
{
	// set object type
	setType("BulletShooter");

	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2); //default to center screen
	setPosition(p);


	// Player controls hero, so register for input events.
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);

	// Need to update rate control each step.
	registerInterest(df::STEP_EVENT);
	setSolidness(df::SPECTRAL); //no sprite but just in case

	fire_slowdown = 30;
	fire_countdown = fire_slowdown;
	LM.writeLog("Spawning BulletShooter");
}

BulletShooter::BulletShooter(df::Vector startPos)
{	// set object type
	setType("BulletShooter");

	setPosition(startPos);
	fire_slowdown = 30;
	fire_countdown = fire_slowdown;

	LM.writeLog("Spawning BulletShooter");
}

BulletShooter::~BulletShooter()
{
	LM.writeLog("Destroying BulletShooter");
}

int BulletShooter::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		//LM.writeLog(" BulletShooter: Step event");
		return 1;
	}

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		LM.writeLog(" BulletShooter: mouse event");
		return 1;
	}

	return 0;
}

void BulletShooter::kbd(const df::EventKeyboard* p_keyboard_event)
{

	//nothing at the moment
}

void BulletShooter::step()
{
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;

}

void BulletShooter::mouse(const df::EventMouse* p_mouse_event)
{
	/*
	// LeftPressed button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT)) //used by block placer
		fire(p_mouse_event->getMousePosition());
	*/

	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::RIGHT))
	{
		//LM.writeLog("BulletShooter: Mouse Event");
		fire(p_mouse_event->getMousePosition());
	}
	

}

void BulletShooter::fire(df::Vector target) //target = mousePOS
{

	// if it can fire
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	// Fire Bullet towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	LM.writeLog("BulletShooter: Pew Pew");
	Bullet* p = new Bullet(getPosition());
	p->setVelocity(v);

	//play sound

}

void BulletShooter::altFire(df::Vector target)
{

	//nothing at the moment
}

