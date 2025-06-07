#include "RegisterLogan.hpp"

#include <Canis/App.hpp>

#include "../ECS/ScriptableEntities/Buildings/HutBase.hpp"
#include "../ECS/ScriptableEntities/Buildings/Hut.hpp"
#include "../ECS/ScriptableEntities/Buildings/Farm.hpp"
#include "../ECS/ScriptableEntities/Buildings/WoodHut.hpp"
#include "../ECS/ScriptableEntities/Buildings/Barracks.hpp"
#include "../ECS/ScriptableEntities/AI/AiBrain.hpp"

void RegisterLogan(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;
    
    REGISTER_SCRIPTABLE_COMPONENT(app, Hut);
    REGISTER_SCRIPTABLE_COMPONENT(app, Farm);
    REGISTER_SCRIPTABLE_COMPONENT(app, WoodHut);
    REGISTER_SCRIPTABLE_COMPONENT(app, Barracks);
    REGISTER_SCRIPTABLE_COMPONENT(app, AiBrain);

    //REGISTER_COMPONENT(app, HealthComponent);
    //REGISTER_COMPONENT_EDITOR(HealthComponent);
}