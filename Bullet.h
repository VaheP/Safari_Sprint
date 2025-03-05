#include "Object.h"
#include "EventCollision.h"

namespace ss
{
    class Bullet : public df::Object
    {
    private:
        void out();
        void hit(const df::EventCollision *p_collision_event);

    public:
        Bullet(df::Vector start_pos);
        int eventHandler(const df::Event *p_e) override;
    };
}
