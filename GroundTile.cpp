#include "GroundTile.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"


ss::GroundTile::GroundTile() {
    setType("GroundTile");
    setSolidness(df::Solidness::SOFT);
    setAltitude(0);
    registerInterest(df::STEP_EVENT);
    setSprite("ground_tile");
}

int ss::GroundTile::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    return 0;
}

void ss::GroundTile::step() {
    df::Vector new_pos = getPosition();
    new_pos.setX(new_pos.getX() - GROUND_SPEED);
    setPosition(new_pos);

    df::Box box = getBox();

    float tile_width = box.getHorizontal();

    if (new_pos.getX() < -tile_width) {
        float rightmost_x = new_pos.getX();
        df::WorldManager &world_manager = df::WorldManager::getInstance();
        df::ObjectList all_objects = world_manager.getAllObjects();
        df::ObjectListIterator li(&all_objects);
        
        while (!li.isDone()) {
            df::Object *p_o = li.currentObject();
            if (p_o->getType() == "GroundTile") {
                float tile_x = p_o->getPosition().getX();
                if (tile_x > rightmost_x)
                    rightmost_x = tile_x;
            }
            li.next();
        }
        new_pos.setX(rightmost_x + tile_width);
        setPosition(new_pos);
    }
}