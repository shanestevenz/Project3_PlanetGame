#pragma once

#include "ViewObject.h"
#include "Event.h"
#define MONEY_STRING "Points"

class Points : public df::ViewObject {

public:
    Points();
    int eventHandler(const df::Event* p_e);
};