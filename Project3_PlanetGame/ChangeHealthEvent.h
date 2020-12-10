#pragma once
#include <Event.h>

const std::string HEALTH_EVENT = "health";

class ChangeHealthEvent : public df::Event
{


public:
    ChangeHealthEvent();
    ChangeHealthEvent(double health);
  
    double healthAmount;

};

