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

Vulture::Vulture(Points* points) {
    setSprite("vulture");
    setType("Vulture");
    setVelocity(df::Vector(-0.75, 0)); // Move a bit faster
    hitPoints = 1;
    p_points = points;
    moveToStart();
}

Vulture::~Vulture() {
    if (p_points) {
        p_points->addScore(10);  // 10 points when Vulture is deleted
    }
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
    if (getPosition().getX() >= 0)
        return;

    if (p_points) {
        //p_points->addScore(5);  // 5 points for dodging
    }

    WM.markForDelete(this);
}

void Vulture::hit(const df::EventCollision* p_collision_event) {
    df::Object* obj1 = p_collision_event->getObject1();
    df::Object* obj2 = p_collision_event->getObject2();

    if (obj1->getType() == "Player" || obj2->getType() == "Player") {
        WM.markForDelete(obj1);
        WM.markForDelete(obj2);
    }
    else if (obj1->getType() == "Bullet" || obj2->getType() == "Bullet") {
        hitPoints--;

        df::Object* bullet = (obj1->getType() == "Bullet") ? obj1 : obj2;
        WM.markForDelete(bullet);

        if (hitPoints <= 0) {
            if (p_points) {
                // p_points->addScore(10);  // 10 points when Panther is destroyed
            }
            WM.markForDelete(this);
        }
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
