#include "Points.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"

Points::Points() {
    setLocation(df::TOP_RIGHT);
    setViewString("Score: 0");  // Initialize with score 0
    setColor(df::YELLOW);
    score = 0;  // Initialize the score value
    registerInterest(df::STEP_EVENT);  // Register for step events
}

int Points::getScore() const {
    return score;
}

// Event handler for step events
int Points::eventHandler(const df::Event* p_e) {
    if (!this) {
        LM.writeLog("Points::eventHandler() - ERROR: this is nullptr!");
        return 0;
    }

    if (p_e->getType() == df::STEP_EVENT) {
        const df::EventStep* p_step_event = dynamic_cast<const df::EventStep*>(p_e);
        if (p_step_event && p_step_event->getStepCount() % 30 == 0) {
            score++;
            setValue(score);
            updatePoints();
        }
        return 1;
    }
    return 0;
}

// Update the points string to reflect the new score
void Points::updatePoints() {
    setViewString("Score: " + std::to_string(score)); // Use actual `score`
}

void Points::addScore(int amount) {
    score += amount; // Update internal score
    //setValue(score); // Update ViewObject's value
    updatePoints();
}