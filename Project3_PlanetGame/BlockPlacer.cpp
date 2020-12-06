#include "BlockPlacer.h"
#include "EventMouse.h"
#include "WorldManager.h"
#include "DisplayManager.h"

BlockPlacer::BlockPlacer()
{
	setType("BlockPlacer");

	//set the blockplacer to Spectral solidness so that it doesn't react to the collision  
	setSolidness(df::SPECTRAL);

	setAltitude(df::MAX_ALTITUDE); // Make blockplacer in foreground

	registerInterest(df::MSE_EVENT);

	// Set starting location in the bottom right of window.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();
	df::Vector p(world_horiz / 2, world_vert / 2);
	setPosition(p);

}

int BlockPlacer::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			// Change location to new mouse position.
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}

	// If get here, have ignored this event.
	return 0;
}

int BlockPlacer::draw() {
	return DM.drawString(getPosition(),"|---|", df::CENTER_JUSTIFIED, df::WHITE);
}
