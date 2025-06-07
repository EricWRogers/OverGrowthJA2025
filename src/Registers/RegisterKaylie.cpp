#include "RegisterKaylie.hpp"
#include "../ECS/ScriptableEntities/Buildings/Sapling.hpp"

#include <Canis/App.hpp>

//#include "Ball.hpp"

void RegisterKaylie(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, Sapling);
}