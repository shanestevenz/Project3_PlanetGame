#include "BlockPlacer.h"
#include <EventStep.h>
#include <LogManager.h>
#include <ResourceManager.h>
#include <EventView.h>
#include "Block.h"
#include "HeavyBlock.h"
#include "Bomb.h"

BlockPlacer::BlockPlacer()
{
	setType("BlockPlacer");

	//set the blockplacer to Spectral solidness so that it doesn't react to the collision  
	setSolidness(df::SPECTRAL);

	setAltitude(df::MAX_ALTITUDE); // Make blockplacer in foreground

	registerInterest(df::MSE_EVENT);


	// Need to update rate control each step.
	registerInterest(df::STEP_EVENT); //needs this for cool down

	// Set starting location in the bottom right of window.
	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2); //default to center screen
	setPosition(p);

	numberOfBlocks = 5;
	currentBlock = NULL;

}

int BlockPlacer::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		
		mouse(p_mouse_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		// every 15 seconds block increments by one for capacity
		if (dynamic_cast <const df::EventStep*> (p_e)->getStepCount() % 450 == 0) {
			step();
		}
		
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

int BlockPlacer::draw() 
{
	return DM.drawString(getPosition(),"|---|", df::CENTER_JUSTIFIED, df::WHITE);
}

void BlockPlacer::step() {

	/*
	if (numberOfBlocks < 5) {
		numberOfBlocks++;
		df::EventView ev("# of Blocks", +1, true); //update UI
		WM.onEvent(&ev);
	}
	*/

}

// Take appropriate action according to mouse action.
void BlockPlacer::mouse(const df::EventMouse* p_mouse_event) {

	if (p_mouse_event->getMouseAction() == df::MOVED) { //when mouse moves, update place location
		// Change location to new mouse position.
		setPosition(p_mouse_event->getMousePosition());

		if (currentBlock != NULL)
		{
			currentBlock->setAvoidCollisions(true);
			
			currentBlock->setPosition(p_mouse_event->getMousePosition());
		}

	}
	// left click
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
	{


		if (currentBlock != NULL) //we have  a block to place
		{

		

			//do some checks to make sure we dont place in bad spots

			df::Vector placePos = getPosition();

			//df::Vector centerScreen(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2);
			//int planetWidth = RM.getSprite("planet")->getWidth();
			//int planetHeight = RM.getSprite("planet")->getHeight();

			if (currentBlock->getType() == "Block")
			{
				LM.writeLog("BlockPlacer: Placing block");

				// Play "purchase" sound.
				df::Sound* p_sound = RM.getSound("purchase");
				p_sound->play();

				(new Block(placePos))->setPlaced(true);
				
			}
			else if (currentBlock->getType() == "HeavyBlock")
			{
				LM.writeLog("BlockPlacer: Placing HEAVY block");

				// Play "purchase" sound.
				df::Sound* p_sound = RM.getSound("purchase");
				p_sound->play();

				(new HeavyBlock(placePos))->setPlaced(true);
			
			}
			else if (currentBlock->getType() == "Bomb")
			{
				LM.writeLog("BlockPlacer: Placing Bomb");

				// Play "puchase" sound.
				df::Sound* p_sound = RM.getSound("purchase");
				p_sound->play();

				(new Bomb(placePos))->setPlaced(true);

			}

			WM.markForDelete(currentBlock);
			currentBlock = NULL;
			

			//RM.getSprite("block")->setColor(df::CYAN);
			//RM.getSprite("explosion")->setColor(df::RED);

			//numberOfBlocks--;
			//df::EventView ev("# of Blocks", -1, true); //update UI
			//WM.onEvent(&ev);

			//placePos.getX() > centerScreen.getX() + planetWidth || placePos.getX() < centerScreen.getX() - planetWidth
			//  && (placePos.getY() > centerScreen.getY() + planetHeight || placePos.getY() < centerScreen.getY() - planetHeight)

		}
		else
		{
			LM.writeLog("BlockPlacer: No block to palce");
			DM.shake(5,10, 5);
			//TODO: play error sound
		}
		
	}

	

}