#pragma region Includes

// Managers
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

#include "AsteroidSpawner.h"

// Game includes.
#include "GameStart.h"
#include "Level.h"
#include "Points.h"
#include "Music.h"
#include "Asteroid.h"
#include "Planet.h"
#include "BulletShooter.h"
#include "BlockPlacer.h"
#include "BigSmile.h"
#include "ChangeBlockButton.h"
#include "Vector.h"
#include "BuyManager.h"

#include "BigLad.h"
#pragma endregion

GameStart::GameStart() {
    setType("GameStart");
    setSprite("gamestart"); //sprite
    setLocation(df::CENTER_CENTER);


    registerInterest(df::KEYBOARD_EVENT); //register event

    p_music = RM.getMusic("theme");
    playMusic();
}

void GameStart::playMusic() {
    p_music->play();
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



    //spawn stuff for this level

    new BigLad;

    new Planet;

    new BulletShooter; //handles shooting bullets

    //new BlockPlacer; //handles placing 

    new BuyManager;
    

    new AsteroidSpawner;
    // new ChangeBlockButton();
    // new BigSmile;

    df::ViewObject* p_Health = new df::ViewObject; // Health Gui 
    p_Health->setLocation(df::TOP_CENTER);
    p_Health->setViewString("Health");
    p_Health->setValue(100);
    p_Health->setColor(df::RED);


    df::ViewObject* p_BlockCount = new df::ViewObject; // Block count Gui
    p_BlockCount->setLocation(df::TOP_RIGHT);
    p_BlockCount->setViewString("# of Blocks");
    p_BlockCount->setValue(5);
    p_BlockCount->setColor(df::BLUE);




    df::ViewObject* p_1 = new df::ViewObject; // Block count Gui
    p_1->setViewString("Block $25");
    p_1->setColor(df::BLUE);
    p_1->setPosition(df::Vector(8, DM.getVertical() - 2));
    p_1->setDrawValue(false);
    //setActive(false);


    df::ViewObject* p_2 = new df::ViewObject; // Block count Gui
    p_2->setViewString("Heavy Block $50");
    p_2->setColor(df::RED);
    p_2->setPosition(df::Vector(25, DM.getVertical() - 2));
    p_2->setDrawValue(false);


    df::ViewObject* p_3 = new df::ViewObject; // Block count Gui
    p_3->setViewString("Bomb $50");
    p_3->setColor(df::GREEN);
    p_3->setPosition(df::Vector(48, DM.getVertical() - 2));
    p_3->setDrawValue(false);


    // Pause start music.
    p_music->pause();

    setActive(false);
}

// Override default draw so as not to display "value".
int GameStart::draw() {
    return df::Object::draw();
}
