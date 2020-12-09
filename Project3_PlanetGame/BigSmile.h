#pragma once
#include "ViewObject.h"
class BigSmile : public df::ViewObject
{



	//df::Music* p_music;
public:
	BigSmile();
	int eventHandler(const df::Event* p_e);
	int draw();

};

