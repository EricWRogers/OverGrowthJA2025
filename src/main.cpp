#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <Canis/App.hpp>

#include "RegisterCanis.hpp"
#include "ECS/ScriptableEntities/UI/RegisterUI.hpp"
#include "ECS/ScriptableEntities/Pong/RegisterPong.hpp"
#include "ECS/ScriptableEntities/Camera/RegisterCamera.hpp"

Canis::App app("SuperPupStudio", "CanisTemplate");

#ifdef __EMSCRIPTEN__
void Loop()
{
    app.Loop();
}
 #endif

int main()
{
    RegisterCanis((void*)&app);
    RegisterPong((void*)&app);
    RegisterUI((void*)&app);
    RegisterCamera((void*)&app);

    // add scene
    app.AddSplashScene(new Canis::Scene("engine_splash", "assets/scenes/engine_splash.scene"));
    app.AddScene(new Canis::Scene("main_menu", "assets/scenes/main_menu.scene"));
    app.AddScene(new Canis::Scene("settings", "assets/scenes/settings.scene"));
    app.AddScene(new Canis::Scene("pong", "assets/scenes/pong.scene"));
    app.AddScene(new Canis::Scene("mesh", "assets/scenes/mesh.scene"));

    app.Run("Canis Template", "mesh");

    #ifdef __EMSCRIPTEN__
    // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
    emscripten_set_main_loop(Loop, 0, true);
    #endif

    return 0;
}