#include "ChangeHealthEvent.h"

ChangeHealthEvent::ChangeHealthEvent()
{
	setType(HEALTH_EVENT);
	healthAmount = 0;
}

ChangeHealthEvent::ChangeHealthEvent(double health)
{
	setType(HEALTH_EVENT);
	healthAmount =  health;
}
