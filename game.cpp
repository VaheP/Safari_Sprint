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

    RM.loadSound("sounds/sfx/step_sand_02.wav", "jump");
}

void populateWorld(void)
{
    new ss::GameStart;
}

int main(int argc, char *argv[])
{
    if (GM.startUp())
    {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    // Load game resources
    loadResources();

    // Populate the world
    populateWorld();

    LM.setFlush(true);

    // df::splash();

    new df::Pause(df::Keyboard::F10);

    GM.run();

    GM.shutDown();

    return 0;
}