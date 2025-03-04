#include "Bullet.h"
#include "EventOut.h"
#include "WorldManager.h"

ss::Bullet::Bullet(df::Vector start_pos) {
    setSprite("bullet");

    setType("Bullet");

    setSolidness(df::SOFT);
    setAltitude(2);

    df::Vector startPos(start_pos.getX() + 3, start_pos.getY());

    setPosition(startPos);

    setSpeed(1.3f);
}


int ss::Bullet::eventHandler(const df::Event *p_e) {
    
    if (p_e -> getType() == df::OUT_EVENT) {
        out();
        return 1;
    }
    else if (p_e -> getType() == df::COLLISION_EVENT) {
        const df::EventCollision *collisionEvent = dynamic_cast <const df::EventCollision *> (p_e);
        hit(collisionEvent);
    }

    return 0;
}

void ss::Bullet::out() {
    if (getPosition().getX() <= WM.getBoundary().getHorizontal() + 1) return;

    WM.markForDelete(this);
}

void ss::Bullet::hit(const df::EventCollision *p_collision_event) {
    if (p_collision_event -> getObject1()->getType() == "Saucer" ||
         p_collision_event -> getObject2() -> getType() == "Saucer") {
        WM.markForDelete(this);
    }

}