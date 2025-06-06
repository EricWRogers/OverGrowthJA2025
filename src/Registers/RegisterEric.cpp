#include "RegisterAiden.hpp"

#include <Canis/App.hpp>

#include "../ECS/Systems/NPCBoidSystem.hpp"
#include "../ECS/ScriptableEntities/Characters/DummyNPC.hpp"
#include "../ECS/ScriptableEntities/Characters/WavePointsManager.hpp"

void RegisterEric(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    app.AddDecodeSystem(DecodeNPCBoidSystem);
    REGISTER_UPDATE_SYSTEM(NPCBoidSystem);

    REGISTER_SCRIPTABLE_COMPONENT(app, DummyNPC);
    REGISTER_SCRIPTABLE_COMPONENT(app, WavePointsManager);
}