#include "AsteroidSpawner.h"
#include "Asteroid.h"
void AsteroidSpawner::step()
{
}

AsteroidSpawner::AsteroidSpawner()
{
	for (int i = 0; i < 15; i++)
		new Asteroid;
}

AsteroidSpawner::~AsteroidSpawner()
{
}

int AsteroidSpawner::eventHandler(const df::Event* p_e)
{
	return 0;
}
