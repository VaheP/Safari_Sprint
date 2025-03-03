#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "Object.h"
#include "EventKeyboard.h"  
#include "Sound.h"

namespace ss {
    class Runner : public df::Object {
        public:
            Runner();
            Runner(df::Vector position);
            int eventHandler(const df::Event *p_e);

            /// @brief Simulates the jump of the runner
            void jump();

            /// @brief Changes the ducking state of the player
            void duck(bool ducking);

            void step();

            void kbd(const df::EventKeyboard *p_keyboard_event);
        private:
            df::Vector m_velocity;
            df::Sound *m_jump_sound;
            float ground_y;
            bool m_grounded;
            bool m_ducking;
    };
}


#endif