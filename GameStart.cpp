#include "GameStart.h"
#include "GroundTile.h"
#include "WorldManager.h"
#include "Runner.h"
#include "Boulder.h"
#include "Panther.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Spawning.h"
#include "GameOver.h"
#include "GameManager.h"
#include "Tree.h"
#include "Points.h"
#include <stdlib.h>	

ss::GameStart::GameStart() {
    setType("StartGame");
    setSprite("game_start");
    setLocation(df::CENTER_CENTER);
    registerInterest(df::KEYBOARD_EVENT);
    setActive(true);
}

void ss::GameStart::start() {
    df::ObjectList all_objects = WM.getAllObjects();
    df::ObjectListIterator it(&all_objects);

    while (!it.isDone()) {
        df::Object* p_o = it.currentObject();
        if (p_o->getType() != "GameStart") {
            WM.markForDelete(p_o);
        }
        it.next();
    }

    if (p_points) {
        WM.markForDelete(p_points);
        p_points = nullptr;
    }

    createGroundTiles();
    p_points = new Points();
    new Runner(df::Vector(10, 19.5));
    new Spawning(p_points);  // Pass Points to Spawning
    setActive(true);
}

void ss::GameStart::createGroundTiles() {

    float world_height = WM.getView().getVertical();

    for (int i = 0; i < TILE_COUNT; ++i) {
        GroundTile* p_tile = new GroundTile();
        df::Box tile_box = p_tile->getBox();
        float tile_width = p_tile->getBox().getHorizontal();
        float tile_height = p_tile->getBox().getVertical();
        float ground_y = world_height - tile_height / 2;
        p_tile->setPosition(df::Vector(i * tile_width, ground_y - 0.5));
    }

    //setActive(false);
}

int ss::GameStart::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);

        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            switch (p_keyboard_event->getKey()) {
            case df::Keyboard::P:
                start();
                break;
            case df::Keyboard::Q:
                GM.shutDown();
                break;
            default:
                break;
            }
        }
        return 1;
    }
    return 0;
}

void ss::GameStart::checkGameOver() {
    df::ObjectList all_objects = WM.getAllObjects();
    df::ObjectListIterator it(&all_objects);

    Runner* p_runner = nullptr;

    // Find Runner object
    while (!it.isDone()) {
        df::Object* p_o = it.currentObject();
        if (p_o->getType() == "Runner") {
            p_runner = dynamic_cast<Runner*>(p_o);
            break;
        }
        it.next();
    }

    if (!p_runner) {
        return;
    }

    // Check for collisions
    df::ObjectList collisions = WM.getCollisions(p_runner, p_runner->getPosition());
    df::ObjectListIterator col_it(&collisions);

    while (!col_it.isDone()) {
        df::Object* p_o = col_it.currentObject();

        if (p_o->getType() == "Boulder" || p_o->getType() == "Panther") {
            LM.writeLog("GameStart: Collision detected! Triggering GameOver.");

            // Spawn GameOver on death
            new GameOver();
            WM.markForDelete(p_runner);
            return;
        }
        col_it.next();
    }
}

void ss::GameStart::checkDodgedObstacles() {
    df::ObjectList all_objects = WM.getAllObjects();
    df::ObjectListIterator it(&all_objects);

    while (!it.isDone()) {
        df::Object* p_o = it.currentObject();

        // If the object is an obstacle (Boulder, Panther, Vulture) and has passed the player
        if (p_o->getType() == "Boulder" || p_o->getType() == "Panther" || p_o->getType() == "Vulture") {
            if (p_o->getPosition().getX() < 0) {  // Assuming obstacles move left and exit at X < 0
                LM.writeLog("GameStart: Obstacle dodged. Adding points.");

                if (p_points) {
                    p_points->addScore(5); // Call `addScore()`
                }

                WM.markForDelete(p_o); // Delete the obstacle
            }
        }
        it.next();
    }
}

/*
void ss::GameStart::spawnBoulder() {
    if (rand() % 100 < 3) {
        LM.writeLog("GameStart: Spawning Boulder.");
        new Boulder();
    }
}

void ss::GameStart::spawnPanther() {
    if (rand() % 200 < 2) {
        LM.writeLog("GameStart: Spawning Panther.");
        new Panther();
    }
} */

void ss::GameStart::spawnTrees() {
    for (int i = 0; i < 5; ++i) {
        new Tree();
    }
}


int ss::GameStart::draw()
{
    return df::Object::draw();
}