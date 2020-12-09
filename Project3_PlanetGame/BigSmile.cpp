#include "BigSmile.h"

BigSmile::BigSmile()
{
    setType("BigSmile");
    setSprite("bigsmile"); //sprite
    setLocation(df::CENTER_CENTER);

    setAltitude(5);
    //registerInterest(df::KEYBOARD_EVENT); //register event
}

int BigSmile::eventHandler(const df::Event* p_e)
{
    return 0;
}

int BigSmile::draw()
{
    return df::Object::draw();
}
