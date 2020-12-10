#include "Wave.h"

Wave::Wave()
{
	asteroidCount = 0; 
	bigLadCount = 0;
	spawnRate = 0; //aseroids per second
	bigLadSpawnTime = {};


}

Wave::Wave(int asteroidCount, double spawnRate)
{


	this->asteroidCount = asteroidCount;
	bigLadCount = 0;
	this->spawnRate = spawnRate;
	bigLadSpawnTime = {};
}

Wave::Wave(int asteroidCount, int bigLadCount, double spawnRate, std::array<double, 5> bigLadSpawnTime)
{

	this->asteroidCount = asteroidCount;
	this->bigLadCount = bigLadCount;
	this->spawnRate = spawnRate;
	this->bigLadSpawnTime = bigLadSpawnTime;

}
