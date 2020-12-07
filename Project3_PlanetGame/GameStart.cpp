#pragma region Includes

// Managers
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameStart.h"

#include "Music.h"
#include "Asteroid.h"
#include "Planet.h"
#include "BulletShooter.h"
#include "Color.h"
#include "Vector.h"
//Events
#include "EventKeyboard.h"

#pragma endregion

GameStart::GameStart() {
    setType("GameStart");
    setSprite("gamestart"); //sprite
    setLocation(df::CENTER_CENTER);


    registerInterest(df::KEYBOARD_EVENT); //register event

   // p_music = RM.getMusic("start music");
    //playMusic();
}

void GameStart::playMusic() {
   // p_music->play();
}

//event handler. returns 0 if ignored
int GameStart::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play game
            start();
            break;
        case df::Keyboard::Q:			// quit game
            GM.setGameOver();
            break;
        default:
            break;
        }
        return 1;
    }

    //ignore
    return 0;
}

void GameStart::start() {  //things that needs to be spawned when the game restarts!



    for (int i = 0; i < 10; i++)
        new Asteroid;
    
   
    new Planet;
  
    new BulletShooter; //cringe but whatever -> creates new planet and then creates bullet shooter at the positon without having to explicitly store pointer reference

    new BlockPlacer;

    //start
    
    df::ViewObject* p_Health = new df::ViewObject; // Health Gui 
    p_Health->setLocation(df::TOP_CENTER);
    p_Health->setViewString("Health");
    p_Health->setValue(3);
    p_Health->setColor(df::RED);
    

    df::ViewObject* p_BlockCount = new df::ViewObject; // Block count Gui
    p_BlockCount->setLocation(df::TOP_RIGHT);
    p_BlockCount->setViewString("# of Blocks");
    p_BlockCount->setValue(5);
    p_BlockCount->setColor(df::BLUE);
    

    // stop the menu music
   // p_music->pause();

    // turn off when game starts
    setActive(false);
}

// Override default draw so as not to display "value".
int GameStart::draw() {
    return df::Object::draw();
}
