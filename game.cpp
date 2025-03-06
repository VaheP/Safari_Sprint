#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Pause.h"
#include "GameStart.h"

void loadResources(void)
{
    RM.loadSprite("sprites/world/ground-tile.txt", "ground_tile");
    RM.loadSprite("sprites/characters/runner.txt", "runner");
    RM.loadSprite("sprites/characters/runner-duck.txt", "runner_duck");
    RM.loadSprite("sprites/characters/rock-spr.txt", "rock");
    RM.loadSprite("sprites/world/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/world/tree-spr1.txt", "tree1");
    RM.loadSprite("sprites/world/tree-spr2.txt", "tree2");
    RM.loadSprite("sprites/world/sun-spr.txt", "sun");
    RM.loadSprite("sprites/characters/panther-spr.txt", "panther");
    RM.loadSprite("sprites/characters/vulture-spr.txt", "vulture");
    RM.loadSprite("sprites/world/gamestart-spr.txt", "game_start");
    RM.loadSprite("sprites/world/gameover-spr.txt", "game_over");                                                                     
    RM.loadSound("sounds/sfx/jump.wav", "jump");
    RM.loadSound("sounds/sfx/kill_enemy.wav", "kill");
    RM.loadSound("sounds/sfx/player_fail.wav", "fail");
    RM.loadSound("sounds/sfx/shoot.wav", "shoot");
    RM.loadMusic("sounds/background/background_sound.wav", "music");
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