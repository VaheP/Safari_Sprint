#ifndef __GROUND_TILE_H__
#define __GROUND_TILE_H__

#include "Object.h"


namespace ss {
    const float GROUND_SPEED = 0.5f;
    class GroundTile : public df::Object {
        public:
            GroundTile();
            int eventHandler(const df::Event *p_e);
            void step();  
    };
}

#endif 