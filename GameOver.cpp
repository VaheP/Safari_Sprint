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

    // Center screen
    setLocation(df::CENTER_CENTER);
    registerInterest(df::STEP_EVENT);
    registerInterest(df::KEYBOARD_EVENT);
}

GameOver::~GameOver() {
    // Delete all objects except GameStart
    df::ObjectList object_list = WM.getAllObjects(true);
    df::ObjectListIterator it(&object_list);

    while (!it.isDone()) {
        df::Object* p_o = it.currentObject();
        if (p_o->getType() != "StartGame") {
            WM.markForDelete(p_o);
        }
        it.next();
    }

    // Create a new GameStart instance if none exists
    bool gameStartExists = false;
    df::ObjectListIterator start_it(&object_list);
    while (!start_it.isDone()) {
        df::Object* p_o = start_it.currentObject();
        if (p_o->getType() == "StartGame") {
            p_o->setActive(true);
            gameStartExists = true;
            break;
        }
        start_it.next();
    }

    if (!gameStartExists) {
        new ss::GameStart();
    }
}

int GameOver::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            switch (p_keyboard_event->getKey()) {
            case df::Keyboard::P:
                new ss::GameStart();  // Restart game
                WM.markForDelete(this);
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

void GameOver::step() {
    time_to_live--;

    if (time_to_live <= 0) {
        WM.markForDelete(this);
    }
}

// Draw game over sprite
int GameOver::draw() {
    return df::Object::draw();
}
