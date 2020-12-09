#pragma once
#include "ViewObject.h"

class Level : public df::ViewObject
{


private:
	void startLevel();
	//df::Music* p_music;
public:
	Level();
	int eventHandler(const df::Event* p_e);
	int draw();


};

