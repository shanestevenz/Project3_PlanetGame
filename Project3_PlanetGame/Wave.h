#pragma once
#include <array>
class Wave
{

public:
	Wave();
	Wave(int asteroidCount, double spawnRate);
	Wave(int asteroidCount, int bigLadCount, double spawnRate, std::array<double, 5> bigLadSpawnTime);

	int asteroidCount;
	int bigLadCount;
	double spawnRate;
	std::array<double,5> bigLadSpawnTime;



};

