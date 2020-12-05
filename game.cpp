#pragma region Includes

//Managers
#include "ResourceManager.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "GameManager.h"

//Objects 
#include "Asteroid.h"

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

}

// Populate world with some objects.
void populateWorld(void) {

	 //create objects
	for (int i = 0; i < 10; i++)
		new Asteroid;
}
