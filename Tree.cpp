#include "Tree.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "EventOut.h"
ss::Tree::Tree()
{
    setType("Tree");
    type1 = rand() % 2;
    if (type1)
    {
        setSprite("tree2");
        y_pos = 10;
    }
    else
    {
        setSprite("tree1");
        y_pos = 13;
    }
    setSolidness(df::SPECTRAL);
    setVelocity(df::Vector((float)-1.0 / (rand() % 10 + 1), 0));
    setAltitude(0);

    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
                 y_pos);
    setPosition(p);
}

int ss::Tree::eventHandler(const df::Event *p_e)
{

    if (p_e->getType() == df::OUT_EVENT)
    {
        out();
        return 1;
    }

    return 0;
}

void ss::Tree::out()
{
    df::Vector p((float)(WM.getBoundary().getHorizontal() + rand() % 20),
                 y_pos);

    setPosition(p);
    setVelocity(df ::Vector(-1.0 / (rand() % 10 + 1), 0));
}