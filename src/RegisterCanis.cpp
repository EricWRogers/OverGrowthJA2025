#include "RegisterCanis.hpp"

#include <Canis/App.hpp>
#include <Canis/Yaml.hpp>
#include <Canis/ECS/Decode.hpp>
#include <Canis/ECS/Encode.hpp>

#include <Canis/ECS/Components/Transform.hpp>
#include <Canis/ECS/Components/Mesh.hpp>
#include <Canis/ECS/Components/DirectionalLight.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>
#include <Canis/ECS/Components/RectTransform.hpp>
#include <Canis/ECS/Components/Color.hpp>
#include <Canis/ECS/Components/Camera2DComponent.hpp>
#include <Canis/ECS/Components/ButtonComponent.hpp>
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/UIImageComponent.hpp>
#include <Canis/ECS/Components/UISliderComponent.hpp>
#include <Canis/ECS/Components/UISliderKnobComponent.hpp>

#include <Canis/ECS/Systems/CollisionSystem.hpp>
#include <Canis/ECS/Systems/UISliderSystem.hpp>
#include <Canis/ECS/Systems/UISliderKnobSystem.hpp>
#include <Canis/ECS/Systems/SpriteAnimationSystem.hpp>

void RegisterCanis(void* _app)
{
    Canis::App& app = *(Canis::App*)_app;

    // decode system
    app.AddDecodeSystem(Canis::DecodeCollisionSystem);
    app.AddDecodeSystem(Canis::DecodeButtonSystem);
    app.AddDecodeSystem(Canis::DecodeUISliderSystem);
    app.AddDecodeSystem(Canis::DecodeUISliderKnobSystem);
    app.AddDecodeSystem(Canis::DecodeSpriteAnimationSystem);

    REGISTER_UPDATE_SYSTEM(Canis::CollisionSystem);
    REGISTER_UPDATE_SYSTEM(Canis::ButtonSystem);
    REGISTER_UPDATE_SYSTEM(Canis::UISliderSystem);
    REGISTER_UPDATE_SYSTEM(Canis::UISliderKnobSystem);
    REGISTER_UPDATE_SYSTEM(Canis::SpriteAnimationSystem);

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
    app.AddDecodeComponent(Canis::DecodeTransform);
    REGISTER_COMPONENT(app, Canis::DirectionalLight);
    REGISTER_COMPONENT(app, Canis::SphereCollider);
    REGISTER_COMPONENT(app, Canis::RectTransform);
    REGISTER_COMPONENT(app, Canis::Color);
    app.AddDecodeComponent(Canis::DecodeTextComponent);
    app.AddDecodeComponent(Canis::DecodeMesh);
    REGISTER_COMPONENT(app, Canis::ButtonComponent);
    REGISTER_COMPONENT(app, Canis::Sprite2DComponent);
    app.AddDecodeComponent(Canis::DecodeUIImageComponent);
    REGISTER_COMPONENT(app, Canis::UISliderComponent);
    REGISTER_COMPONENT(app, Canis::UISliderKnobComponent);
    app.AddDecodeComponent(Canis::DecodeSpriteAnimationComponent);
    REGISTER_COMPONENT(app, Canis::Camera2DComponent);

    // encode component
    app.AddEncodeComponent(Canis::EncodeTagComponent);
    app.AddEncodeComponent(Canis::EncodeTransform);
    app.AddEncodeComponent(EncodeComponent<Canis::DirectionalLight>);
    app.AddEncodeComponent(EncodeComponent<Canis::SphereCollider>);
    app.AddEncodeComponent(Canis::EncodeMesh);
    app.AddEncodeComponent(EncodeComponent<Canis::RectTransform>);
    app.AddEncodeComponent(Canis::EncodeColor);
    app.AddEncodeComponent(Canis::EncodeTextComponent);
    app.AddEncodeComponent(EncodeComponent<Canis::ButtonComponent>);
    app.AddEncodeComponent(EncodeComponent<Canis::Sprite2DComponent>);
    app.AddEncodeComponent(Canis::EncodeUIImageComponent);
    app.AddEncodeComponent(EncodeComponent<Canis::UISliderComponent>);
    app.AddEncodeComponent(EncodeComponent<Canis::UISliderKnobComponent>);
    app.AddEncodeComponent(EncodeComponent<Canis::Camera2DComponent>);

    REGISTER_COMPONENT_EDITOR(Canis::TagComponent);
    REGISTER_COMPONENT_EDITOR(Canis::Transform);
    REGISTER_COMPONENT_EDITOR(Canis::Mesh);
    REGISTER_COMPONENT_EDITOR(Canis::DirectionalLight);
    REGISTER_COMPONENT_EDITOR(Canis::SphereCollider);
    REGISTER_COMPONENT_EDITOR(Canis::RectTransform);
    REGISTER_COMPONENT_EDITOR(Canis::Camera2DComponent);
    REGISTER_COMPONENT_EDITOR(Canis::Color);
    REGISTER_COMPONENT_EDITOR(Canis::TextComponent);
    REGISTER_COMPONENT_EDITOR(Canis::ButtonComponent);
    REGISTER_COMPONENT_EDITOR(Canis::Sprite2DComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UIImageComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderKnobComponent);
}
