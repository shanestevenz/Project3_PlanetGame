#include "AsteroidSpawner.h"
#include "Asteroid.h"
#include "BigLad.h"
#include "GameWin.h"
#include "NextWave.h"
#include <EventStep.h>
#include <EventView.h>
#include <LogManager.h>
#include <GameManager.h>


AsteroidSpawner::AsteroidSpawner()
{

	timeBetweenWaves = 10;

	betweenWaveTimer = timeBetweenWaves;
	
	currentWaveTimer = 0; //should this count down or up? when is wave over? after killin all asteroids or surviving for certain amount of time????
	
	waveIndex = 7;
	waveState = START;

	spawnTimer = 0; 

	//init waves heres, hard coded

	Wave wave1 = Wave(10,2);
	Wave wave2 = Wave(20, 3);
	Wave wave3 = Wave(20, 4);
	Wave wave4 = Wave(20, 1, 4, {20,0,0,0,0});

	Wave wave5 = Wave(20, 1, 5, { 20,0,0,0,0 });
	Wave wave6 = Wave(20, 2, 5, { 10,20,0,0,0 });
	Wave wave7 = Wave(20, 2, 6, { 20,0,0,0,0 });
	Wave wave8 = Wave(20, 3, 5, { 10,20,30,0,0 });


	waves.push_back(wave1);
	waves.push_back(wave2);
	waves.push_back(wave3);

	waves.push_back(wave4);
	waves.push_back(wave5);
	waves.push_back(wave6);
	waves.push_back(wave7);
	waves.push_back(wave8);

	registerInterest(df::STEP_EVENT);
}

AsteroidSpawner::~AsteroidSpawner()
{
}

int AsteroidSpawner::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		if (dynamic_cast <const df::EventStep*> (p_e)->getStepCount() % 30 == 0)
			step();
		return 1;
	}
	return 0;
}




void AsteroidSpawner::step() //lots of logic here
{
	

	if (waveState == START)//first time logic here
	{
		currentWaveTimer = 0;
		spawnTimer = waves[waveIndex].spawnRate;

		LM.writeLog("Spawner: Start wave %d", waveIndex);
	
		waveState = ONGOING;
	}
	else if (waveState == ONGOING)//bulk logic here
	{
		LM.writeLog("Spawner: Wave %d ONGING", waveIndex);
		


		for (int i = 0; i < waves[waveIndex].spawnRate; i++) ///asteroids per second
		{
			new Asteroid;
			LM.writeLog("Spawner: spawning asteroid");
		}
		
		/*spawnTimer--;
		if (spawnTimer <= 0)  //i ditched this approach
		{
			
			//spawn asteroid!
			new Asteroid;
			new Asteroid;
			new Asteroid;
			LM.writeLog("Spawner: spawning asteroid");
			spawnTimer = waves[waveIndex].spawnRate;

		}
		*/
		for (int i = 0; i < waves[waveIndex].bigLadCount; i++)
		{
			if (currentWaveTimer == waves[waveIndex].bigLadSpawnTime[i])
			{
				new BigLad;
			}

		}



		currentWaveTimer++;

		if (currentWaveTimer > 45 ) //if wave lasts longer than 100 seconds, wave is over
		{
		
		
			LM.writeLog("Spawner: CLEAR WAVE %d and and go to inbetween", waveIndex);


			LM.writeLog("Spawner: CLEAR WAVE and between");
			waveState = INBETWEEN;
			betweenWaveTimer = timeBetweenWaves;

			currentWaveTimer = betweenWaveTimer;
			//stop last wave
			clearWave();

		}

	}
	else if (waveState == INBETWEEN)
	{
		
		betweenWaveTimer--;
		currentWaveTimer = betweenWaveTimer;
		if (betweenWaveTimer <= 0)
		{
			//nEXT WAVET
		
			waveIndex++;
			LM.writeLog("Spawner:  NEXT WAVE %d startin soon ", waveIndex);
			if (waveIndex >= waves.size()) //no more waves!
			{
				waveState = STOPPED;
			}
			else
			{
				waveState = START;
				new NextWave;
			}



		}


		//count down and set up next wave when ready
	}
	else if (waveState == STOPPED)
	{
		new GameWin;
		LM.writeLog("Spawner: Wave Stopped at index %d", waveIndex);
		//Do nothing
	}


	df::EventView ev("Wave #", waveIndex + 1, false); //Set Wave
	WM.onEvent(&ev);

	df::EventView ev2("CurrentWave", currentWaveTimer, false); //Set Wave
	WM.onEvent(&ev2);

}

void AsteroidSpawner::clearWave()
{


	// remove all wave stuff
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Asteroid" || p_o->getType() == "BigLad" || p_o->getType() == "Block" || p_o->getType() == "Bomb" || p_o->getType() == "HeavyBlock" || p_o->getType() == "Bullet")
			WM.markForDelete(p_o);


	}

}