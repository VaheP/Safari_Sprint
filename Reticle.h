#include "Object.h"
#define RETICLE_CHAR '+'
#pragma once

namespace ss
{
    class Reticle : public df::Object
    {
    public:
        Reticle();
        int draw(void) override;
        int eventHandler(const df::Event *p_e) override;
    };
}