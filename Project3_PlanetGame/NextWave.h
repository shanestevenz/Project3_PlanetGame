#pragma once

#include "ViewObject.h"

class NextWave : public df::ViewObject {


private:
	int time_to_live;
	void step();

public:
	NextWave();
	~NextWave();
	int eventHandler(const df::Event* p_e);
	int draw();


};

