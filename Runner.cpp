#include "Runner.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameOver.h"
#include "Bullet.h"

ss::Runner::Runner() {
    float world_height = WM.getView().getVertical();
    float player_height = getBox().getVertical();
    Runner(df::Vector(10, world_height - player_height / 2 + 0.5));
}

ss::Runner::Runner(df::Vector position) {
    setType("Player");
    setSprite("runner");
    m_jump_sound = RM.getSound("jump");
    setAltitude(2);
    fire_slowdown = 10;
    fire_countdown = fire_slowdown;
    m_velocity = df::Vector(0, 0);
    m_grounded = true;
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
    registerInterest(df::MSE_EVENT);
    ground_y = position.getY();
    setPosition(position);
    m_reticle = new Reticle();
}

ss::Runner::~Runner() {
    new GameOver();
}

int ss::Runner::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT)
    {
        const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);

        kbd(p_keyboard_event);
        return 1;
    }
    if (p_e->getType() == df::MSE_EVENT)
    {
        const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*>(p_e);
        mouse(p_mouse_event);
        return 1;
    }
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    return 0;
}

void ss::Runner::kbd(const df::EventKeyboard* p_keyboard_event)
{
    switch (p_keyboard_event->getKey())
    {
    case df::Keyboard::SPACE:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            jump();
        break;
    case df::Keyboard::S:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            duck(true);
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            duck(false);
        break;
    default:
        break;
    }
}

void ss::Runner::mouse(const df::EventMouse *p_mouse_event)
{
    if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
        fire(p_mouse_event->getMousePosition());
}

void ss::Runner::fire(df::Vector target)
{
    if (fire_countdown > 0)
        return;
    fire_countdown = fire_slowdown;

    df::Vector v = target - getPosition();

    v.normalize();
    v.scale(1);

    ss::Bullet *p = new Bullet(getPosition());
    p->setVelocity(v);

    df::Sound *p_sound = RM.getSound("fire");
    if (p_sound)
    {
        p_sound->play();
    }
}

void ss::Runner::duck(bool ducking) {
    if (m_grounded) {
        m_ducking = ducking;
        if (m_ducking) {
            setPosition(df::Vector(getPosition().getX(), ground_y + 0.5));
            setSprite("runner_duck");
        }
        else {
            setPosition(df::Vector(getPosition().getX(), ground_y));
            setSprite("runner");
        }
    }
}

void ss::Runner::step() {
    const float GRAVITY = 0.13f;

    if (!m_grounded) {
        m_velocity.setY(m_velocity.getY() + GRAVITY);
    }

    df::Vector pos = getPosition();
    pos.setY(pos.getY() + m_velocity.getY());
    setPosition(pos);

    if (pos.getY() >= ground_y) {
        pos.setY(ground_y);
        setPosition(pos);
        m_velocity.setY(0);
        m_grounded = true;
    }

    fire_countdown--;
    if (fire_countdown < 0)
        fire_countdown = 0;

}

void ss::Runner::jump() {
    if (m_grounded && !m_ducking) {
        m_jump_sound->play();
        m_velocity.setY(-1.5f);
        m_grounded = false;
    }
}