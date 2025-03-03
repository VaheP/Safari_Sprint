#include "ViewObject.h"

namespace ss
{
    const int TILE_COUNT = 10; 
    class GameStart : public df::ViewObject
    {
    private:
        void start();
        void createGroundTiles();

    public:
        GameStart();
    };
}