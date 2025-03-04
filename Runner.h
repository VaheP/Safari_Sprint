#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "Object.h"
#include "EventKeyboard.h"  
#include "EventMouse.h"
#include "Sound.h"
#include "Reticle.h"

namespace ss {
    class Runner : public df::Object {
        public:
            Runner();
            ~Runner();
            Runner(df::Vector position);
            int eventHandler(const df::Event *p_e);

            /// @brief Simulates the jump of the runner
            void jump();

            /// @brief Changes the ducking state of the player
            void duck(bool ducking);

            void step();

            void kbd(const df::EventKeyboard *p_keyboard_event);

            void mouse(const df::EventMouse *p_mouse_event);

            void fire(df::Vector target);

        private:
            df::Vector m_velocity;
            df::Sound *m_jump_sound;
            float ground_y;
            bool m_grounded;
            bool m_ducking;
            Reticle *m_reticle;
            int fire_countdown;
            int fire_slowdown;

    };
}


#endif