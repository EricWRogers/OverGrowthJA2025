#include "RegisterPong.hpp"

#include <Canis/App.hpp>

#include "Ball.hpp"
#include "Paddle.hpp"
#include "TimerTimer.hpp"

void RegisterPong(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, Ball);
    REGISTER_SCRIPTABLE_COMPONENT(app, Paddle);
    REGISTER_SCRIPTABLE_COMPONENT(app, TimerTimer2D);
}