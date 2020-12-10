#include "NextWave.h"
#include <EventStep.h>
#include <WorldManager.h>
#include <DisplayManager.h>

void NextWave::step()
{
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);

}

NextWave::NextWave()
{


    setType("NextWave");

    setSprite("nextwave");
   
    time_to_live = 90;

    setPosition(df::Vector(DM.getHorizontal()/2, 5));

    registerInterest(df::STEP_EVENT); //  step event.

}

NextWave::~NextWave()
{
}

int NextWave::eventHandler(const df::Event* p_e)
{
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

int NextWave::draw()
{
    return df::Object::draw();
}
