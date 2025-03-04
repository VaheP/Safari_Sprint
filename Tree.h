#include "Object.h"

namespace ss
{
    class Tree : public df::Object
    {
    private:
        void out();
        bool type1;
        int y_pos;

    public:
        Tree();
        int eventHandler(const df::Event *p_e) override;
    };
}