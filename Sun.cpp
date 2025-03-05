#include "Sun.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "EventOut.h"

ss::Sun::Sun()
{
    setType("Sun");
    setSprite("sun");

    setSolidness(df::SPECTRAL);
    setAltitude(0);
}
