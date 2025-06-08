#include "RegisterEric.hpp"

#include <Canis/App.hpp>

#include "../ECS/Systems/BillboardSystem.hpp"
#include "../ECS/Systems/NPCBoidSystem.hpp"
#include "../ECS/ScriptableEntities/Characters/DummyNPC.hpp"
#include "../ECS/ScriptableEntities/Characters/WavePointsManager.hpp"
#include "../ECS/ScriptableEntities/Buildings/Temp3DSprite.hpp"


#include <Canis/ECS/Systems/CollisionSystem.hpp>

void RegisterEric(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    app.AddDecodeSystem(DecodeNPCBoidSystem);
    REGISTER_UPDATE_SYSTEM(NPCBoidSystem);

    app.AddDecodeSystem(DecodeBillboardSystem);
    REGISTER_UPDATE_SYSTEM(BillboardSystem);

    app.AddDecodeSystem(Canis::DecodeCollisionSystem);
    REGISTER_UPDATE_SYSTEM(Canis::CollisionSystem);

    REGISTER_SCRIPTABLE_COMPONENT(app, DummyNPC);
    REGISTER_SCRIPTABLE_COMPONENT(app, WavePointsManager);
    REGISTER_SCRIPTABLE_COMPONENT(app, Temp3DSprite);
}
