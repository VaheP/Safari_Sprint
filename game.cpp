#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Pause.h"

void loadResources(void)
{

}

void populateWorld(void)
{

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