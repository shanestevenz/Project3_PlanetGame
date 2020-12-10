#pragma once
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
//#include "Reticle.h"
#include "EventCollision.h"


#include <list>
#include <vector>
#include "Wave.h"
class AsteroidSpawner : public df::Object
{

private:
    void step();



public:
    AsteroidSpawner();
    ~AsteroidSpawner();
    int eventHandler(const df::Event* p_e);
    std::vector<Wave> waves = {};
    int waveIndex;
    double timeBetweenWaves;
    double betweenWaveTimer;

    double currentWaveTimer;


    double spawnTimer;
   enum WaveState waveState ;

    void clearWave();

};

   enum  WaveState
{
    ONGOING,
    INBETWEEN,
    STOPPED,
    START

};