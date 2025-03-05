#ifndef BOULDER_H
#define BOULDER_H

#include "Object.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "Points.h"

class Boulder : public df::Object {
private:
    void moveToStart();
    void hit(const df::EventCollision* p_collision_event);
    void out();
    Points* p_points;

public:
    Boulder(Points* points);
    ~Boulder();
    int eventHandler(const df::Event* p_e) override;
};

#endif