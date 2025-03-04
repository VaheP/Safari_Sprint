#include "ViewObject.h"
#include "Points.h"

namespace ss
{
    const int TILE_COUNT = 10;
    class GameStart : public df::ViewObject
    {
    private:
        void start();
        void createGroundTiles();
        void spawnBoulder();
        void spawnPanther();
        Points* p_points;
        int eventHandler(const df::Event* p_e);
        void checkGameOver();
        void spawnTrees();
        int draw(void);

    public:
        GameStart();
    };
}