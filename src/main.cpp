#ifdef _WIN32
#include <windows.h>
#endif

#include <Canis/App.hpp>
#include <Canis/ECS/Decode.hpp>
#include <Canis/ECS/Encode.hpp>

#include <Canis/ECS/Systems/UISliderSystem.hpp>
#include <Canis/ECS/Systems/UISliderKnobSystem.hpp>

#include "ECS/ScriptableEntities/DebugCamera2D.hpp"
#include "ECS/ScriptableEntities/SplashLoader.hpp"
#include "ECS/ScriptableEntities/MainMenuButtons.hpp"

int main(int argc, char* argv[])
{
    Canis::App app("SuperPupStudio", "StopTheSlimesDemo");

    // decode system
    app.AddDecodeSystem(Canis::DecodeButtonSystem);
    
    // decode render system
    app.AddDecodeRenderSystem(Canis::DecodeRenderHUDSystem);
    app.AddDecodeRenderSystem(Canis::DecodeRenderTextSystem);
    app.AddDecodeRenderSystem(Canis::DecodeSpriteRenderer2DSystem);

    // decode scriptable entities
    app.AddDecodeScriptableEntity(DecodeDebugCamera2D);
    app.AddDecodeScriptableEntity(DecodeSplashLoader);
    app.AddDecodeScriptableEntity(DecodeMainMenuButtons);

    // decode component
    app.AddDecodeComponent(Canis::DecodeTagComponent);
    app.AddDecodeComponent(Canis::DecodeCamera2DComponent);
    app.AddDecodeComponent(Canis::DecodeRectTransformComponent);
    app.AddDecodeComponent(Canis::DecodeColorComponent);
    app.AddDecodeComponent(Canis::DecodeTextComponent);
    app.AddDecodeComponent(Canis::DecodeButtonComponent);
    app.AddDecodeComponent(Canis::DecodeSprite2DComponent);
    app.AddDecodeComponent(Canis::DecodeUIImageComponent);
    app.AddDecodeComponent(Canis::DecodeUISliderComponent);
    app.AddDecodeComponent(Canis::DecodeSpriteAnimationComponent);    

    // encode component
    app.AddEncodeComponent(Canis::EncodeTransformComponent);
    app.AddEncodeComponent(Canis::EncodeRectTransformComponent);
    app.AddEncodeComponent(Canis::EncodeColorComponent);
    app.AddEncodeComponent(Canis::EncodeTagComponent);
    app.AddEncodeComponent(Canis::EncodeTextComponent);
    app.AddEncodeComponent(Canis::EncodeButtonComponent);

    // encode scriptable component
    app.AddEncodeScriptableEntity(EncodeMainMenuButtons);

    // add scene
    //app.AddSplashScene(new Canis::Scene("engine_splash", "assets/scenes/engine_splash.scene"));
    app.AddSplashScene(new Canis::Scene("main_menu", "main_menu"));

    app.Run("Canis | Stop The Slimes","main_menu");

    return 0;
}