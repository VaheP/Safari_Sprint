#include "GameOver.h"
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "GameStart.h"

GameOver::GameOver() {
    setType("GameOver");
    if (setSprite("game_over") == 0) {
        time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
    }
    else {
        time_to_live = 120;
    }

    // Center on screen
    setLocation(df::CENTER_CENTER);

    registerInterest(df::STEP_EVENT);
}

GameOver::~GameOver() {
    // Delete all objects to clean up world
    df::ObjectList object_list = WM.getAllObjects(true);
    df::ObjectListIterator it(&object_list);

    while (!it.isDone()) {
        df::Object* p_o = it.currentObject();
        WM.markForDelete(p_o);
        it.next();
    }
}

int GameOver::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    return 0;
}

void GameOver::step() {
    time_to_live--;
    if (time_to_live <= 0) {
        GM.shutDown();  // Quit program
    }
}

// Draw Game Over sprite
int GameOver::draw() {
    return df::Object::draw();
}
