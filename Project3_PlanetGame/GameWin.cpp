#include "GameWin.h"



#pragma region Includes
//Managers
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameStart.h"

//events
#include "EventStep.h"
#pragma endregion
GameWin::GameWin() {


    // df::Sound* p_sound = RM.getSound("game over");// gameover sound.
     //p_sound->play();
    setType("GameWin");

    setSprite("gamewin");
    
    time_to_live = 120;


    setLocation(df::CENTER_CENTER); //center 


    registerInterest(df::STEP_EVENT); //  step event.

}

// When game over is doen clean up for restart
GameWin::~GameWin() {

    // Remove Saucers and ViewObjects, re-activate GameStart.
    df::ObjectList object_list = WM.getAllObjects(true);
    df::ObjectListIterator i(&object_list);
    for (i.first(); !i.isDone(); i.next()) {
        df::Object* p_o = i.currentObject();
        // if (p_o->getType() == "Asteroid" || p_o->getType() == "ViewObject" || p_o->getType() == "Block")
           // WM.markForDelete(p_o);

        if (p_o->getType() == "GameStart") {
            p_o->setActive(true);
            dynamic_cast <GameStart*> (p_o)->playMusic(); // Resume start music.
        }
        else
        {
            WM.markForDelete(p_o);
        }

    }
}

// Eventhandler: Return 1 if handled. else 0 if ignored
int GameWin::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Timer for message
void GameWin::step() {
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);
}

// Override default draw so as not to display "value".
int GameWin::draw() {
    return df::Object::draw();
}
