#pragma once
#include "Object.h"
#include <Color.h>
class Explosion : public df::Object {

private:
    int time_to_live;
    void step();

public:
    Explosion();
    Explosion(df::Color color);
    int eventHandler(const df::Event* p_e);
};