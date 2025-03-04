#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "Reticle.h"

ss::Reticle::Reticle() {
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

    registerInterest(df::MSE_EVENT);

    int worldHoriz = (int) WM.getBoundary().getHorizontal();

    int worldVert = (int) WM.getBoundary().getVertical();

    df::Vector pos (worldHoriz/2, worldVert/2);

    setPosition(pos);
}


int ss::Reticle::eventHandler(const df::Event *p_e) {
    if (p_e -> getType() == df::MSE_EVENT) {
        const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);

        if (p_mouse_event -> getMouseAction() == df::MOVED) {
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }
    }

    return 0;
}

int ss::Reticle::draw() {
    return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}