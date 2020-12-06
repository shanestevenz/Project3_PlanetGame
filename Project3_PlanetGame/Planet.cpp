#include "Planet.h"
#include "Gameover.h"
#include <EventOut.h>
#include <WorldManager.h>
#include <EventView.h>
#include <DisplayManager.h>



Planet::Planet()
{

	setSprite("planet");

	// set object type
	setType("Planet");

	p_blockplacer = new BlockPlacer;

	df::Vector p(WM.getBoundary().getHorizontal()/2 , WM.getBoundary().getVertical()/2 );
	//df::Vector p(10, 4);
	setPosition(p);
}



int Planet::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::OUT_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
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
		health--;
		df::EventView ev2("Health", -1, true);
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

}



Planet::~Planet()
{

	// Shake screen (severity 20 pixels x&y, duration 10 frames).
	DM.shake(20, 20, 10);

	// Create GameOver object.
	new GameOver;
}