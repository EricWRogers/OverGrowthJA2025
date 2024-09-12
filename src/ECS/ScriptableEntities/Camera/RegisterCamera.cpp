#include "RegisterCamera.hpp"

#include <Canis/App.hpp>

#include "FlyCam.hpp"
#include "DebugCamera2D.hpp"

void RegisterCamera(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, FlyCam);
    REGISTER_SCRIPTABLE_COMPONENT(app, DebugCamera2D);
}