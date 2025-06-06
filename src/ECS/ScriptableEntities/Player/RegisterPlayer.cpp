#include "RegisterPlayer.hpp"

#include <Canis/App.hpp>

#include "PlayerCamera.hpp"
#include "PlayerMovement.hpp"

void RegisterPlayer(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, PlayerCamera);
    REGISTER_SCRIPTABLE_COMPONENT(app, PlayerMovement);
}