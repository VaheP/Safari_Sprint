#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Pause.h"
#include "GameStart.h"

void loadResources(void)
{
    RM.loadSprite("sprites/ground-tile.txt", "ground_tile");
    RM.loadSprite("sprites/runner.txt", "runner");
    RM.loadSprite("sprites/runner-duck.txt", "runner_duck");
    RM.loadSprite("sprites/characters/rock-spr.txt", "rock");
    RM.loadSprite("sprites/characters/panther-spr.txt", "panther");
    RM.loadSprite("sprites/world/gamestart-spr.txt", "game_start");

    RM.loadSound("sounds/sfx/step_sand_02.wav", "jump");
}

void populateWorld(void)
{
    new ss::GameStart;
}

int main(int argc, char* argv[])
{
    df::GameManager& game_manager = df::GameManager::getInstance();
    if (game_manager.startUp()) {
        df::LogManager& log_manager = df::LogManager::getInstance();
        log_manager.writeLog("Error starting game manager!");
        game_manager.shutDown();
        return 0;
    }

    LM.setFlush(true);

    // Load game resources
    loadResources();

    // Populate the world
    populateWorld();


    //df::splash();

    new df::Pause(df::Keyboard::F10);

    GM.run();

    GM.shutDown();

    return 0;
}