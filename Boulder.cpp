#include <stdlib.h>		// for rand()

#include "Boulder.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Points.h"

Boulder::Boulder(Points* points) {
    setSolidness(df::SOFT);
    setSprite("rock");
    setType("Boulder");
    setVelocity(df::Vector(-0.85, 0));
    p_points = points;
    moveToStart();
}

Boulder::~Boulder() {
    if (p_points) {
        //p_points->addScore(5);  // 5 points when Boulder is deleted
    }
}

void Boulder::out() {
    if (getPosition().getX() >= 0)
        return;

    if (p_points) {
        p_points->addScore(5);  // 5 points for dodging
    }

    WM.markForDelete(this);
}

void Boulder::moveToStart() {
    df::Vector temp_pos;
    int world_horiz = (int)WM.getBoundary().getHorizontal();
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
    float boulder_height = getBox().getVertical();

    temp_pos.setX(highest_x + 5);
    temp_pos.setY(ground_y - (boulder_height / 2));

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
        // Kill player on contact
        WM.markForDelete(p_collision_event->getObject1());
        WM.markForDelete(p_collision_event->getObject2());
    }
    else if (p_collision_event->getObject1()->getType() == "Bullet" ||
        p_collision_event->getObject2()->getType() == "Bullet") {

        df::Object* bullet = (p_collision_event->getObject1()->getType() == "Bullet") // Deletes only bullet
            ? p_collision_event->getObject1()
            : p_collision_event->getObject2();

        WM.markForDelete(bullet);
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