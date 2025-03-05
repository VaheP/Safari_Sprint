#include "Spawning.h"
#include "Boulder.h"
#include "Panther.h"
#include "Vulture.h"
#include "LogManager.h"
#include "EventStep.h"
#include "Points.h"
#include <stdlib.h>

Spawning::Spawning(Points* points) {
    setType("Spawning");
    p_points = points;
    spawn_timer = 150;  // Initial spawn delay
    registerInterest(df::STEP_EVENT);
}

int Spawning::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        if (!p_points) return 0;  // Safety check in case Points is missing
        int score = p_points->getScore();

        int max_spawn_rate = 50;
        int base_spawn_rate = 150;
        int score_threshold = 50;

        int new_spawn_rate = base_spawn_rate - (score / score_threshold) * 10;
        if (new_spawn_rate < max_spawn_rate) {
            new_spawn_rate = max_spawn_rate;
        }

        spawn_timer--;

        if (spawn_timer <= 0) {
            spawnEnemy();
            spawn_timer = new_spawn_rate;
        }

        return 1;
    }
    return 0;
}

void Spawning::spawnEnemy() {
    int spawnRoll = rand() % 3;

    if (spawnRoll == 0) {
        new Boulder(p_points);
    }
    else if (spawnRoll == 1) {
        new Panther(p_points);
    }
    else {
        new Vulture(p_points);
    }
}
