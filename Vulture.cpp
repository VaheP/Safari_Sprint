#include <stdlib.h> // for rand()
#include "Vulture.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Points.h"

Vulture::Vulture() {
    // Setup for sprite
    setSprite("vulture");

    // Set object type
    setType("Vulture");
    setAltitude(2);

    setVelocity(df::Vector(-0.8, 0));  // Move a bit faster than other objects

    hitPoints = 1;
    moveToStart();
}

Vulture::~Vulture() {
    df::EventView ev(POINTS_STRING, 10, true);
    WM.onEvent(&ev);
}

void Vulture::moveToStart() {
    df::Vector temp_pos;

    int world_horiz = WM.getBoundary().getHorizontal();
    int world_vert = WM.getBoundary().getVertical();

    temp_pos.setX(world_horiz + 5);
    temp_pos.setY(world_vert * 0.7); // Spawn at roughly eye-level of player

    // Ensure no collisions at spawn point
    df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
    while (!collision_list.isEmpty()) {
        temp_pos.setX(temp_pos.getX() - 1);
        collision_list = WM.getCollisions(this, temp_pos);
    }

    WM.moveObject(this, temp_pos);
}

void Vulture::out() {
    // If it moves off the left side, delete it
    if (getPosition().getX() < 0) {
        WM.markForDelete(this);
    }
}

void Vulture::hit(const df::EventCollision* p_collision_event) {
    df::Object* obj1 = p_collision_event->getObject1();
    df::Object* obj2 = p_collision_event->getObject2();
    df::Object* other = (obj1 == this) ? obj2 : obj1;

    // Handle collision with player
    if (other->getType() == "Player") {
        LM.writeLog("Vulture hit Runner. Marking both for deletion.");
        WM.markForDelete(other);
        WM.markForDelete(this);
    }
    else if (other->getType() == "Bullet") {
        hitPoints--;
        if (hitPoints <= 0) {
            LM.writeLog("Vulture destroyed. Marking for deletion.");
            df::EventView ev("Score", 10, true);
            WM.onEvent(&ev);
            WM.markForDelete(this);
        }
        WM.markForDelete(other);
    }
}


int Vulture::eventHandler(const df::Event* p_e) {
    if (dynamic_cast<const df::EventOut*>(p_e)) {
        out();
        return 1;
    }
    else if (dynamic_cast<const df::EventCollision*>(p_e)) {
        hit(static_cast<const df::EventCollision*>(p_e));
        return 1;
    }
    return 0;
}
