#include "GameStart.h"
#include "GroundTile.h"
#include "WorldManager.h"
#include "Runner.h"
#include "Boulder.h"
#include "Panther.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Spawning.h"
#include <stdlib.h>	

ss::GameStart::GameStart() {
    setType("GameStart");
    setLocation(df::CENTER_CENTER);
    p_points = new Points();
    start();
}

void ss::GameStart::start() {
    createGroundTiles();
    new Runner(df::Vector(10, 19.5));
    new Spawning();
    setActive(false);
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
    if (p_e->getType() == df::STEP_EVENT) {
        LM.writeLog("GameStart: Step event received! Checking spawn...");
        spawnBoulder();
        spawnPanther();
        return 1;
    }
    LM.writeLog("GameStart: Step event NOT received.");
    return 0;
}

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
}