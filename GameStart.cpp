#include "GameStart.h"
#include "GroundTile.h"
#include "WorldManager.h"
#include "Runner.h"

ss::GameStart::GameStart() {
    setType("GameStart");
    setLocation(df::CENTER_CENTER);
    start();
}

void ss::GameStart::start() {
    createGroundTiles();
    new Runner(df::Vector(10,19.5));
}

void ss::GameStart::createGroundTiles() {

    float world_height = WM.getView().getVertical();

    for (int i = 0; i < TILE_COUNT; ++i) {
        GroundTile *p_tile = new GroundTile();
        df::Box tile_box = p_tile->getBox();
        float tile_width = p_tile->getBox().getHorizontal();
        float tile_height = p_tile->getBox().getVertical();
        float ground_y = world_height - tile_height/2;
        p_tile->setPosition(df::Vector(i * tile_width, ground_y-0.5));
    }

    setActive(false);
}