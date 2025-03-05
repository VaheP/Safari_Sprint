#include <stdlib.h>		// for rand()

#include "Panther.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Points.h"

Panther::Panther(Points* points) {
    setSprite("panther");
    setType("Panther");
    setVelocity(df::Vector(-0.7, 0));
    hitPoints = 2;
    p_points = points;
    moveToStart();
}


Panther::~Panther() {
    if (p_points) {
        p_points->addScore(10);  // 10 points when Panther is deleted
    }
}

void Panther::out() {
    if (getPosition().getX() >= 0)
        return;

    if (p_points) {
        p_points->addScore(5);  // 5 points for dodging
    }

    WM.markForDelete(this);
}

void Panther::moveToStart() {
    df::Vector temp_pos;
    int world_horiz = (int)WM.getBoundary().getHorizontal();

    // Find rightmost ground tile
    df::ObjectList ground_tiles = WM.getAllObjects();
    df::ObjectListIterator li(&ground_tiles);
    float highest_x = 0;
    float ground_y = 0;

    while (!li.isDone()) {
        df::Object* p_o = li.currentObject();
        if (p_o->getType() == "GroundTile") {
            float tile_x = p_o->getPosition().getX();
            if (tile_x > highest_x) {
                highest_x = tile_x;
                ground_y = p_o->getPosition().getY();
            }
        }
        li.next();
    }

    // Get height
    float panther_height = getBox().getVertical();

    // Set position with bottom of sprite aligned to the ground
    temp_pos.setX(highest_x + 5);
    temp_pos.setY(ground_y - (panther_height / 2));
    df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
    while (!collision_list.isEmpty()) {
        temp_pos.setX(temp_pos.getX() + 1);
        collision_list = WM.getCollisions(this, temp_pos);
    }

    WM.moveObject(this, temp_pos);
}


void Panther::hit(const df::EventCollision* p_collision_event) {
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


int Panther::eventHandler(const df::Event* p_e) {
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