#include "ExplosionEvent.h"


ExplosionEvent::ExplosionEvent() 
{
	setType(EXPLOSION_EVENT);
	explosionDamage = 1000;
	explosionRange = 1000;
}
ExplosionEvent::ExplosionEvent(df::Vector explosionPos, double explosionRange)
{
	setType(EXPLOSION_EVENT);
	this->explosionPos = explosionPos;
	this->explosionRange = explosionRange;
	explosionDamage = 1000;
}

