#include "RegisterAiden.hpp"

#include <Canis/App.hpp>

//#include "Ball.hpp"
#include "../ECS/Components/Health.hpp"
#include "../ECS/ScriptableEntities/Buildings/TownHall.hpp"
#include "../ECS/ScriptableEntities/Characters/NPC.hpp"

void RegisterAiden(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    //REGISTER_SCRIPTABLE_COMPONENT(app, Ball);
    REGISTER_SCRIPTABLE_COMPONENT(app, TownHall);
    //REGISTER_SCRIPTABLE_COMPONENT(app, NPC);
    REGISTER_COMPONENT(app, HealthComponent);
    app.AddEncodeComponent(EncodeComponent<HealthComponent>);
    REGISTER_COMPONENT_EDITOR(HealthComponent);
}