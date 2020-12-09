#include "Event.h"
#include <Vector.h>

const std::string EXPLOSION_EVENT = "explosion";

class ExplosionEvent : public df::Event {

public:
    ExplosionEvent();
    ExplosionEvent(df::Vector explosionPos, double explosionRange);
    df::Vector explosionPos;
    double explosionRange;
    double explosionDamage;
};