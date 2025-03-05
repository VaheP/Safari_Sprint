#ifndef SPAWNING_H
#define SPAWNING_H

#include "Event.h"
#include "Object.h"
#include "Vector.h"
#include "Points.h"

class Spawning : public df::Object {
private:
    int spawn_timer;  // Global timer for obstacles
    void spawnEnemy();  // Spawns obstacle
    Points* p_points;
public:
    Spawning(Points* points);
    int eventHandler(const df::Event* p_e) override;
};

#endif // SPAWNING_H
