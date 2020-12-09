#pragma once
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
//#include "Reticle.h"
#include "EventCollision.h"

class AsteroidSpawner : public df::Object
{

private:
    void step();



public:
    AsteroidSpawner();
    ~AsteroidSpawner();
    int eventHandler(const df::Event* p_e);




};

