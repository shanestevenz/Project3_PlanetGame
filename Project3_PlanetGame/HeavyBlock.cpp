#include "HeavyBlock.h"
#include <LogManager.h>


HeavyBlock::HeavyBlock()
{

	setSprite("heavyblock");

	// set object type
	setType("HeavyBlock");
	setPlaced(false);
	durability = 10;
	LM.writeLog("Heavy Block placed");
}

HeavyBlock::HeavyBlock(df::Vector pos)
{

	setSprite("heavyblock");

	// set object type
	setType("HeavyBlock");
	setPlaced(false);
	durability = 10;
	setPosition(pos);

	LM.writeLog("Heavy Block placed");
}

HeavyBlock::~HeavyBlock()
{
	//Explosion* p_explosion = new Explosion(df::YELLOW);
	//p_explosion->setPosition(this->getPosition());
	//LM.writeLog("Heavy Block Destroyed");
}

