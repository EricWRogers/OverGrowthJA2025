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

Canis::App* appPointer = new Canis::App("SuperPupStudio", "CanisTemplate");
Canis::App& app = *appPointer;

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

    app.Run("Canis Template");

    #ifdef __EMSCRIPTEN__
    // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
    emscripten_set_main_loop(Loop, 0, true);
    #endif

    // might turn off asset manager or delete it manually
    delete appPointer;

    return 0;
}