#include "Spawning.h"
#include "Boulder.h"
#include "Panther.h"
#include "Vulture.h"
#include "LogManager.h"
#include "EventStep.h"
#include <stdlib.h>

Spawning::Spawning() {
    setType("Spawning");
    registerInterest(df::STEP_EVENT);

    // Initial spawn timer
    spawn_timer = (rand() % 100);
}

int Spawning::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        spawn_timer--;

        if (spawn_timer <= 0) {
            spawnEnemy();
            spawn_timer = (rand() % 100) + 50;  // Spawns new obstacle every 50-150 steps
        }

        return 1;
    }
    return 0;
}

void Spawning::spawnEnemy() {
    int spawnRoll = rand() % 3; // 3 possible outcomes

    if (spawnRoll == 0) {
        LM.writeLog("Spawner: Spawning Boulder.");
        new Boulder();
    }
    else if (spawnRoll == 1) {
        LM.writeLog("Spawner: Spawning Panther.");
        new Panther();
    }
    else {
        LM.writeLog("Spawner: Spawning Vulture.");
        new Vulture();
    }
}
