

#pragma region Includes



//managers
#include "LogManager.h"
//objects
#include "Points.h"

//events
#include "Event.h"
#include "EventStep.h"
#pragma endregion

Points::Points()
{
	setLocation(df::TOP_LEFT);
	setViewString(MONEY_STRING);
	setColor(df::YELLOW);
	// register to update 
	registerInterest(df::STEP_EVENT);


}

// Eventhandler: Return 1 if handled. else 0 if ignored
int Points::eventHandler(const df::Event* p_e) {

	//score update
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	//increase score every second
	if (p_e->getType() == df::STEP_EVENT) {
		if (dynamic_cast <const df::EventStep*> (p_e)->getStepCount() % 30 == 0)
			setValue(getValue() + 1);
		return 1;
	}

	// ignore event
	return 0;
}
