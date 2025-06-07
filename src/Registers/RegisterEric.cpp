#include "RegisterAiden.hpp"

#include <Canis/App.hpp>

#include "../ECS/ScriptableEntities/Characters/WavePointsManager.hpp"

void RegisterEric(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, WavePointsManager);
}