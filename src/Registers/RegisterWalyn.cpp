#include "RegisterWalyn.hpp"

#include <Canis/App.hpp>

#include "../ECS/ScriptableEntities/Player/PlayerBuildInput.hpp"
#include "../ECS/ScriptableEntities/Player/Resources.hpp"

void RegisterWalyn(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, PlayerBuildInput);
    REGISTER_SCRIPTABLE_COMPONENT(app, Resources);
}