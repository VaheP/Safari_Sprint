#ifndef PANTHER_H
#define PANTHER_H

#include "Object.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
//#include "Player.h"

class Panther : public df::Object {
private:
    int hitPoints;
    void moveToStart();
    void hit(const df::EventCollision* p_collision_event);
    void out();

public:
    Panther();
    ~Panther();
    int eventHandler(const df::Event* p_e) override;
};

#endif#pragma once
