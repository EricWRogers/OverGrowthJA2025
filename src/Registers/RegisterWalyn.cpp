#include "RegisterWalyn.hpp"

#include <Canis/App.hpp>

//#include "Ball.hpp"
#include "../ECS/ScriptableEntities/Player/PlayerBuildInput.hpp"

void RegisterWalyn(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, PlayerBuildInput);
}