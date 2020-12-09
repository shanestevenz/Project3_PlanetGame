#include "Bomb.h"

#include <LogManager.h>
#include "Explosion.h"
#include "Points.h"
#include <EventView.h>
#include "ExplosionEvent.h"
#include <WorldManager.h>

Bomb::Bomb()
{
	setSprite("bomb");

	// set object type
	setType("Bomb");

	durability = 1;
	explosionRange = 25;
	LM.writeLog("Bomb placed");
	setPlaced(false);
}

Bomb::Bomb(df::Vector pos)
{

	setSprite("bomb");
	setPlaced(false);
	// set object type
	setType("Bomb");

	durability = 1;
	explosionRange = 25;
	setPosition(pos);
	LM.writeLog("Bomb placed");

}

Bomb::~Bomb()
{
	

	LM.writeLog("Bomb Destroyed");
}

void Bomb::hit(const df::EventCollision* p_c)
{



	if (!placed)
	{
		return;
	}


	LM.writeLog("Bomb: hit!");

	if (((p_c->getObject2()->getType()) == "Asteroid") || ((p_c->getObject1()->getType()) == "Asteroid") || ((p_c->getObject2()->getType()) == "BigLad") || ((p_c->getObject1()->getType()) == "BigLad") )
	{
		Explosion* p_explosion = new Explosion(df::YELLOW);
		p_explosion->getAnimation().getSprite()->setColor(df::RED);   //explode
		p_explosion->setPosition(this->getPosition());


		df::addParticles(df::SPARKS, getPosition(), 3, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 2, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);

		df::EventView ev(MONEY_STRING, +10, true); //give Money
		WM.onEvent(&ev);
		

		LM.writeLog("Bomb: Sending explosion event");
		ExplosionEvent ex(getPosition(), explosionRange); //send explostion event
		ex.explosionDamage = 25;
		WM.onEvent(&ex);


		// Play "big explosion" sound.
		df::Sound* p_sound = RM.getSound("big explosion");
		p_sound->play();

		WM.markForDelete(this);  //explode
		LM.writeLog("Bomb hit: %s on %s", p_c->getObject1()->getType(), p_c->getObject2()->getType());

	}




}
