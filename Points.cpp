#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventView.h"

#include "Points.h"

Points::Points() {
    setLocation(df::TOP_RIGHT);
    setViewString(POINTS_STRING);
    setColor(df::YELLOW);

    // Need to update score each second, so count "step" events
    registerInterest(df::STEP_EVENT);
}

// Event handler
int Points::eventHandler(const df::Event* p_e) {
    if (df::ViewObject::eventHandler(p_e)) {
        return 1;
    }

    // Handle step events for scoring.
    if (p_e->getType() == df::STEP_EVENT) {
        const df::EventStep* p_step_event = dynamic_cast<const df::EventStep*>(p_e);
        if (p_step_event && p_step_event->getStepCount() % 30 == 0) {
            setValue(getValue() + 1); // Increment score
            updatePoints();
        }
        return 1;
    }

    return 0;
}

void Points::updatePoints() {
    // Check if score meets point threshold
}