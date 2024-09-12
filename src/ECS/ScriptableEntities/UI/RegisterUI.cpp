#include "RegisterUI.hpp"

#include <Canis/App.hpp>

#include "SplashLoader.hpp"
#include "MainMenuButtons.hpp"
#include "SettingsMenuFunctions.hpp"

void RegisterUI(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    REGISTER_SCRIPTABLE_COMPONENT(app, SplashLoader);
    REGISTER_SCRIPTABLE_COMPONENT(app, MainMenuButtons);
    REGISTER_SCRIPTABLE_COMPONENT(app, SettingsMenuFunctions);
}