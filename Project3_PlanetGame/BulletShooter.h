#pragma once


#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
//#include "Reticle.h"
#include "EventCollision.h"

class BulletShooter : public df::Object
{

private:
    void kbd(const df::EventKeyboard* p_keyboard_event);
   
    void step();

    

    void fire(df::Vector target);
    void altFire(df::Vector target);

    void mouse(const df::EventMouse* p_mouse_event);

    //Reticle* p_reticle;
 


public:
    BulletShooter();
    ~BulletShooter();
    int eventHandler(const df::Event* p_e);


};

