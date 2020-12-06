#pragma region Includes

//Managers
#include "ResourceManager.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "GameManager.h"

//Objects 
#include "Asteroid.h"
#include "Planet.h"
#include "GameStart.h"
#include <ViewObject.h>
#pragma endregion

// Function prototypes.
void loadResources(void);
void populateWorld(void);


int main(int argc, char* argv[])
{


	//game manager

  // Start up game manager.
	if (GM.startUp()) {
		LM.writeLog("Error starting game manager!");
		GM.shutDown();
		return 0;
	}

	LM.setFlush(true);

	// Load game resources.
	loadResources();

	// Populate game world with some objects.
	populateWorld();

	GM.run();

	// Shut everything down.
	GM.shutDown();

}


// Load resources (sprites, sound effects, music).
void loadResources(void) {
	//rm load stuff
	RM.loadSprite("sprites/asteroid-spr.txt", "asteroid");
	RM.loadSprite("sprites/planet-spr.txt", "planet");
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");
	RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
	RM.loadSprite("sprites/bullet-spr.txt", "bullet");
	RM.loadSprite("sprites/explosion-spr.txt", "explosion");
}

// Populate world with some objects.
void populateWorld(void) {


	new GameStart(); //game start object
}
