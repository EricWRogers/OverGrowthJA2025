#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>

#include <Canis/App.hpp>
#include <Canis/Yaml.hpp>
#include <Canis/ECS/Decode.hpp>
#include <Canis/ECS/Encode.hpp>

#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/UIImageComponent.hpp>
#include <Canis/ECS/Components/UISliderComponent.hpp>
#include <Canis/ECS/Components/UISliderKnobComponent.hpp>

#include <Canis/ECS/Systems/UISliderSystem.hpp>
#include <Canis/ECS/Systems/UISliderKnobSystem.hpp>

#include "ECS/ScriptableEntities/DebugCamera2D.hpp"
#include "ECS/ScriptableEntities/SplashLoader.hpp"
#include "ECS/ScriptableEntities/MainMenuButtons.hpp"

#include "ECS/ScriptableEntities/Pong/Ball.hpp"
#include "ECS/ScriptableEntities/Pong/Paddle.hpp"

Canis::App app("SuperPupStudio", "StopTheSlimesDemo");

#ifdef __EMSCRIPTEN__
void Loop()
{
    app.Loop();
}
 #endif

int main()
{
    // decode system
    app.AddDecodeSystem(Canis::DecodeButtonSystem);
    app.AddDecodeSystem(Canis::DecodeUISliderSystem);
    app.AddDecodeSystem(Canis::DecodeUISliderKnobSystem);

    REGISTER_UPDATE_SYSTEM(Canis::ButtonSystem);
    REGISTER_UPDATE_SYSTEM(Canis::UISliderSystem);
    REGISTER_UPDATE_SYSTEM(Canis::UISliderKnobSystem);

    // decode render system
    app.AddDecodeRenderSystem(Canis::DecodeRenderHUDSystem);
    app.AddDecodeRenderSystem(Canis::DecodeRenderTextSystem);
    app.AddDecodeRenderSystem(Canis::DecodeSpriteRenderer2DSystem);

    REGISTER_RENDER_SYSTEM(Canis::RenderHUDSystem);
    REGISTER_RENDER_SYSTEM(Canis::RenderTextSystem);
    REGISTER_RENDER_SYSTEM(Canis::SpriteRenderer2DSystem);

    // decode component
    app.AddDecodeComponent(Canis::DecodeTagComponent);
    REGISTER_COMPONENT(app, Canis::RectTransformComponent);
    REGISTER_COMPONENT(app, Canis::ColorComponent);
    app.AddDecodeComponent(Canis::DecodeTextComponent);
    REGISTER_COMPONENT(app, Canis::ButtonComponent);
    REGISTER_COMPONENT(app, Canis::Sprite2DComponent);
    //app.AddDecodeComponent(Canis::DecodeSprite2DComponent);
    app.AddDecodeComponent(Canis::DecodeUIImageComponent);
    REGISTER_COMPONENT(app, Canis::UISliderComponent);
    REGISTER_COMPONENT(app, Canis::UISliderKnobComponent);
    app.AddDecodeComponent(Canis::DecodeSpriteAnimationComponent);
    REGISTER_COMPONENT(app, Canis::Camera2DComponent);

    // encode component
    app.AddEncodeComponent(Canis::EncodeTagComponent);
    app.AddEncodeComponent(Canis::EncodeTransformComponent);
    app.AddEncodeComponent(Canis::EncodeRectTransformComponent);
    app.AddEncodeComponent(Canis::EncodeColorComponent);
    app.AddEncodeComponent(Canis::EncodeTextComponent);
    app.AddEncodeComponent(EncodeComponent<Canis::ButtonComponent>);
    app.AddEncodeComponent(EncodeComponent<Canis::Sprite2DComponent>);
    app.AddEncodeComponent(Canis::EncodeUIImageComponent);
    app.AddEncodeComponent(EncodeComponent<Canis::UISliderComponent>);
    app.AddEncodeComponent(EncodeComponent<Canis::UISliderKnobComponent>);
    app.AddEncodeComponent(EncodeComponent<Canis::Camera2DComponent>);

    REGISTER_COMPONENT_EDITOR(Canis::TagComponent);
    REGISTER_COMPONENT_EDITOR(Canis::TransformComponent);
    REGISTER_COMPONENT_EDITOR(Canis::RectTransformComponent);
    REGISTER_COMPONENT_EDITOR(Canis::Camera2DComponent);
    REGISTER_COMPONENT_EDITOR(Canis::ColorComponent);
    REGISTER_COMPONENT_EDITOR(Canis::TextComponent);
    REGISTER_COMPONENT_EDITOR(Canis::ButtonComponent);
    REGISTER_COMPONENT_EDITOR(Canis::Sprite2DComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UIImageComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderKnobComponent);

    // scriptable component
    REGISTER_SCRIPTABLE_COMPONENT(app, DebugCamera2D);
    REGISTER_SCRIPTABLE_COMPONENT(app, SplashLoader);
    REGISTER_SCRIPTABLE_COMPONENT(app, MainMenuButtons);
    REGISTER_SCRIPTABLE_COMPONENT(app, Ball);
    REGISTER_SCRIPTABLE_COMPONENT(app, Paddle);

    // add scene
    app.AddSplashScene(new Canis::Scene("engine_splash", "assets/scenes/engine_splash.scene"));
    app.AddScene(new Canis::Scene("main_menu", "assets/scenes/main_menu.scene"));
    app.AddScene(new Canis::Scene("settings", "assets/scenes/settings.scene"));
    app.AddScene(new Canis::Scene("pong", "assets/scenes/pong.scene"));

    app.Run("Canis | Stop The Slimes", "settings");

    #ifdef __EMSCRIPTEN__
    // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
    emscripten_set_main_loop(Loop, 0, true);
    #endif

    return 0;
}