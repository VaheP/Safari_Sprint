#include <stdlib.h>		// for rand()

#include "Panther.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Points.h"

Panther::Panther() {

    // Setup for sprite
    setSprite("panther");

    // Set object type
    setType("Panther");

    setVelocity(df::Vector(-0.7, 0)); // move left every 4 steps

    hitPoints = 2;

    // Move Obstacle to start location
    moveToStart();
}

Panther::~Panther() {
    df::EventView ev(POINTS_STRING, 10, true);
    WM.onEvent(&ev);
}

void Panther::out() {
    // Check if object has moved off the left edge
    if (getPosition().getX() >= 0)
        return;

    // Add 5 points on despawn
    df::EventView ev("Score", 5, true);
    WM.onEvent(&ev);

    // Delete
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

    // Get Panther's height
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
    if (p_collision_event->getObject1()->getType() == "Player" ||
        p_collision_event->getObject2()->getType() == "Player") {
        WM.markForDelete(p_collision_event->getObject1());
        WM.markForDelete(p_collision_event->getObject2());
    }
    else if (p_collision_event->getObject1()->getType() == "Bullet" || // For shooting enemy
        p_collision_event->getObject2()->getType() == "Bullet") {
        hitPoints--;
        if (hitPoints <= 0) {
            df::EventView ev("Score", 10, true);
            WM.onEvent(&ev);
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