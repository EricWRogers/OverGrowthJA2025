#include "RegisterCanis.hpp"

#include <Canis/App.hpp>
#include <Canis/Yaml.hpp>
#include <Canis/ECS/Decode.hpp>
#include <Canis/ECS/Encode.hpp>

#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/Camera2DComponent.hpp>
#include <Canis/ECS/Components/ButtonComponent.hpp>
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/UIImageComponent.hpp>
#include <Canis/ECS/Components/UISliderComponent.hpp>
#include <Canis/ECS/Components/UISliderKnobComponent.hpp>

#include <Canis/ECS/Systems/UISliderSystem.hpp>
#include <Canis/ECS/Systems/UISliderKnobSystem.hpp>

void RegisterCanis(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

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
    app.AddDecodeRenderSystem(Canis::DecodeRenderMeshSystem);

    REGISTER_RENDER_SYSTEM(Canis::RenderHUDSystem);
    REGISTER_RENDER_SYSTEM(Canis::RenderTextSystem);
    REGISTER_RENDER_SYSTEM(Canis::SpriteRenderer2DSystem);
    REGISTER_RENDER_SYSTEM(Canis::RenderMeshSystem);

    // decode component
    app.AddDecodeComponent(Canis::DecodeTagComponent);
    app.AddDecodeComponent(Canis::DecodeTransformComponent);
    REGISTER_COMPONENT(app, Canis::SphereColliderComponent);
    REGISTER_COMPONENT(app, Canis::RectTransformComponent);
    REGISTER_COMPONENT(app, Canis::ColorComponent);
    app.AddDecodeComponent(Canis::DecodeTextComponent);
    app.AddDecodeComponent(Canis::DecodeMeshComponent);
    REGISTER_COMPONENT(app, Canis::ButtonComponent);
    REGISTER_COMPONENT(app, Canis::Sprite2DComponent);
    app.AddDecodeComponent(Canis::DecodeUIImageComponent);
    REGISTER_COMPONENT(app, Canis::UISliderComponent);
    REGISTER_COMPONENT(app, Canis::UISliderKnobComponent);
    app.AddDecodeComponent(Canis::DecodeSpriteAnimationComponent);
    REGISTER_COMPONENT(app, Canis::Camera2DComponent);

    REGISTER_COMPONENT_EDITOR(Canis::TagComponent);
    REGISTER_COMPONENT_EDITOR(Canis::TransformComponent);
    REGISTER_COMPONENT_EDITOR(Canis::MeshComponent);
    REGISTER_COMPONENT_EDITOR(Canis::SphereColliderComponent);
    REGISTER_COMPONENT_EDITOR(Canis::RectTransformComponent);
    REGISTER_COMPONENT_EDITOR(Canis::Camera2DComponent);
    REGISTER_COMPONENT_EDITOR(Canis::ColorComponent);
    REGISTER_COMPONENT_EDITOR(Canis::TextComponent);
    REGISTER_COMPONENT_EDITOR(Canis::ButtonComponent);
    REGISTER_COMPONENT_EDITOR(Canis::Sprite2DComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UIImageComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderKnobComponent);


}