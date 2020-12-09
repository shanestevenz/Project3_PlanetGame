#pragma once
#include "ViewObject.h"
#include "EventKeyboard.h"
#include "Points.h"
#include "BlockPlacer.h"
class BuyManager: public df::ViewObject {

private:
	void step();
	bool buy(int price);
public:
	BuyManager();
	~BuyManager();
	int eventHandler(const df::Event* p_e);
	int draw();
	int money;
	Points* moneyView;
	BlockPlacer* blockPlacer;
	void kbd(const df::EventKeyboard* p_keyboard_event);




};

