#ifndef VULTURE_H
#define VULTURE_H

#include "Object.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"

class Vulture : public df::Object {
private:
    int hitPoints;
    int startY;
    int movementPhase;
    bool swooping;
    bool targetingPlayer;
    void moveToStart();
    void hit(const df::EventCollision* p_collision_event);
    void out();

public:
    Vulture();
    ~Vulture();
    int eventHandler(const df::Event* p_e) override;
};

#endif#pragma once
