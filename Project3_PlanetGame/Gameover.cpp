
#pragma region Includes
//Managers
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameOver.h"

//events
#include "EventStep.h"
#pragma endregion
GameOver::GameOver() {


   // df::Sound* p_sound = RM.getSound("game over");// gameover sound.
    //p_sound->play();
    setType("GameOver");


    if (setSprite("gameover") == 0) //sprite
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    else
        time_to_live = 0;


    setLocation(df::CENTER_CENTER); //center 


    registerInterest(df::STEP_EVENT); //  step event.

}

// When game over is doen clean up for restart
GameOver::~GameOver() {

    // Remove Saucers and ViewObjects, re-activate GameStart.
    df::ObjectList object_list = WM.getAllObjects(true);
    df::ObjectListIterator i(&object_list);
    for (i.first(); !i.isDone(); i.next()) {
        df::Object* p_o = i.currentObject();
        if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject")
            WM.markForDelete(p_o);
        /*
        if (p_o->getType() == "GameStart") {
            p_o->setActive(true);
            dynamic_cast <GameStart*> (p_o)->playMusic(); // Resume start music.
        }
        */
    }
}

// Eventhandler: Return 1 if handled. else 0 if ignored
int GameOver::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Timer for message
void GameOver::step() {
    time_to_live--;
    if (time_to_live <= 0)
        WM.markForDelete(this);
}

// Override default draw so as not to display "value".
int GameOver::draw() {
    return df::Object::draw();
}
