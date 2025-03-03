#include <stdlib.h>		// for rand()

#include "Boulder.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Points.h"

Boulder::Boulder() {

    // Setup for sprite
    setSprite("rock");

    // Set object type
    setType("Rock");

    // Set speed in horizontal direction
    setVelocity(df::Vector(-0.25, 0)); // move left every 4 steps

    // Move Obstacle to start location
    moveToStart();
}

Boulder::~Boulder() {
    df::EventView ev(POINTS_STRING, 5, true);
    WM.onEvent(&ev);
}

void Boulder::out() {
    // Check if object has moved off the left edge
    if (getPosition().getX() >= 0)
        return;

    // Add 5 points on despawn
    df::EventView ev("Score", 5, true);
    WM.onEvent(&ev);

    // Mark for deletion
    WM.markForDelete(this);
}

void Boulder::moveToStart() {
    df::Vector temp_pos;
    int world_horiz = (int)WM.getBoundary().getHorizontal();

    // Find the rightmost ground tile
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

    // Get the Panther's height
    float panther_height = getBox().getVertical();

    // Set position with bottom of sprite aligned to the ground
    temp_pos.setX(highest_x + 5); // A little further ahead
    temp_pos.setY(ground_y - (panther_height / 2)); // Adjust so bottom aligns with ground

    // Ensure no collisions at spawn point
    df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
    while (!collision_list.isEmpty()) {
        temp_pos.setX(temp_pos.getX() + 1);
        collision_list = WM.getCollisions(this, temp_pos);
    }

    WM.moveObject(this, temp_pos);
}

void Boulder::hit(const df::EventCollision* p_collision_event) {
    if (p_collision_event->getObject1()->getType() == "Player" ||
        p_collision_event->getObject2()->getType() == "Player") {
        // Kill the player on contact
        WM.markForDelete(p_collision_event->getObject1());
        WM.markForDelete(p_collision_event->getObject2());
    }
}

int Boulder::eventHandler(const df::Event* p_e) {
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