#ifdef _WIN32
#include <windows.h>
#endif

#include <Canis/App.hpp>
#include <Canis/Yaml.hpp>
#include <Canis/ECS/Decode.hpp>
#include <Canis/ECS/Encode.hpp>

#include <Canis/ECS/Components/UIImageComponent.hpp>
#include <Canis/ECS/Components/UISliderComponent.hpp>
#include <Canis/ECS/Components/UISliderKnobComponent.hpp>

#include <Canis/ECS/Systems/UISliderSystem.hpp>
#include <Canis/ECS/Systems/UISliderKnobSystem.hpp>

#include "ECS/ScriptableEntities/DebugCamera2D.hpp"
#include "ECS/ScriptableEntities/SplashLoader.hpp"
#include "ECS/ScriptableEntities/MainMenuButtons.hpp"

//////////////// HELL

template <typename ComponentType>
void DecodeComponent(YAML::Node &_n, Canis::Entity &_entity, Canis::SceneManager *_sceneManager)
{
    if (auto componentNode = _n[std::string(type_name<ComponentType>())])
    {
        auto &component = _entity.AddComponent<ComponentType>();
        auto &registry = GetPropertyRegistry<ComponentType>();

        for (const auto &[propertyName, setter] : registry.setters)
        {
            if (componentNode[propertyName])
            {
                YAML::Node propertyNode = componentNode[propertyName];
                setter(propertyNode, &component, _sceneManager);
            }
        }
    }
}

template <typename ComponentType>
void EncodeComponent(YAML::Emitter &_out, Canis::Entity &_entity)
{
    if (_entity.HasComponent<ComponentType>())
    {
        ComponentType& component = _entity.GetComponent<ComponentType>();

        _out << YAML::Key << std::string(type_name<ComponentType>());
        _out << YAML::BeginMap;

        auto &registry = GetPropertyRegistry<ComponentType>();
        for (const auto &propertyName : registry.propertyOrder)
        {
            _out << YAML::Key << propertyName << YAML::Value << registry.getters[propertyName](&component);
        }

        _out << YAML::EndMap;
    }
}

#define REGISTER_COMPONENT(AppInstance, ComponentType)                      \
{                                                                           \
    static bool registered = (ComponentType::RegisterProperties(), true);   \
    AppInstance.AddDecodeComponent(DecodeComponent<ComponentType>);         \
    /*AppInstance.AddEncodeComponent(EncodeComponent<ComponentType>);*/     \
}

#define REGISTER_UPDATE_SYSTEM(system)                                      \
{                                                                           \
    GetSystemRegistry().updateSystems.push_back(#system);                   \
}

#define REGISTER_RENDER_SYSTEM(system)                                      \
{                                                                           \
    GetSystemRegistry().renderSystems.push_back(#system);                   \
}

#define REGISTER_COMPONENT_NAME(component)                                  \
{                                                                           \
    GetComponent().names.push_back(#component);                             \
}

#define REGISTER_COMPONENT_EDITOR(component)                                                    \
{                                                                                               \
	GetComponent().addComponentFuncs[#component] = [](Canis::Entity &_entity) { 			    \
		if (_entity.HasComponent<component>() == false) { _entity.AddComponent<component>(); }  \
	};                                                                                          \
    GetComponent().removeComponentFuncs[#component] = [](Canis::Entity &_entity) {              \
        if (_entity.HasComponent<component>()) { _entity.RemoveComponent<component>(); }        \
    };                                                                                          \
    GetComponent().hasComponentFuncs[#component] = [](Canis::Entity &_entity) -> bool {         \
        return _entity.HasComponent<component>();                                               \
    };                                                                                          \
	GetComponent().names.push_back(#component);  									            \
}

//////////////// EXIT HELL

//////////////// DECODE

template <typename ComponentType>
bool DecodeScriptComponent(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == std::string(type_name<ComponentType>()))
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<ComponentType>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}

template <typename ComponentType>
std::function<bool(const std::string &, Canis::Entity &)> CreateDecodeFunction()
{
    return [](const std::string &_name, Canis::Entity &_entity) -> bool
    {
        return DecodeScriptComponent<ComponentType>(_name, _entity);
    };
}

template <typename ComponentType>
bool EncodeScriptComponent(YAML::Emitter &_out, Canis::ScriptableEntity *_scriptableEntity)
{
    if (auto castedEntity = dynamic_cast<ComponentType *>(_scriptableEntity))
    {
        _out << YAML::Key << "Canis::ScriptComponent" << YAML::Value << std::string(type_name<ComponentType>()); // typeid(ComponentType).name();
        return true;
    }
    return false;
}

template <typename ComponentType>
std::function<bool(YAML::Emitter &, Canis::ScriptableEntity *)> CreateEncodeFunction()
{
    return [](YAML::Emitter &_out, Canis::ScriptableEntity *_scriptableEntity) -> bool
    {
        return EncodeScriptComponent<ComponentType>(_out, _scriptableEntity);
    };
}

#define REGISTER_SCRIPTABLE_COMPONENT(AppInstance, ComponentType)                                                   \
{                                                                                                                   \
    AppInstance.AddEncodeScriptableEntity(CreateEncodeFunction<ComponentType>());                                   \
    AppInstance.AddDecodeScriptableEntity(CreateDecodeFunction<ComponentType>());                                   \
    GetScriptableComponentRegistry().addScriptableComponent[#ComponentType] = [](Canis::Entity &_entity) { 		    \
		if (_entity.HasScript<ComponentType>() == false) { _entity.AddScript<ComponentType>(); }                    \
	};                                                                                                              \
    GetScriptableComponentRegistry().removeScriptableComponent[#ComponentType] = [](Canis::Entity &_entity) {       \
        if (_entity.HasScript<ComponentType>()) { _entity.RemoveScript(); }                                         \
    };                                                                                                              \
    GetScriptableComponentRegistry().hasScriptableComponent[#ComponentType] = [](Canis::Entity &_entity) -> bool {  \
        return _entity.HasScript<ComponentType>();                                                                  \
    };                                                                                                              \
    GetScriptableComponentRegistry().names.push_back(#ComponentType);                                               \
}

int main(int argc, char *argv[])
{
    Canis::App app("SuperPupStudio", "StopTheSlimesDemo");

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
    app.AddDecodeComponent(Canis::DecodeSprite2DComponent);
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
    app.AddEncodeComponent(Canis::EncodeUIImageComponent);
    app.AddEncodeComponent(EncodeComponent<Canis::UISliderComponent>);
    app.AddEncodeComponent(EncodeComponent<Canis::UISliderKnobComponent>);

    REGISTER_COMPONENT_EDITOR(Canis::TagComponent);
    REGISTER_COMPONENT_EDITOR(Canis::TransformComponent);
    REGISTER_COMPONENT_EDITOR(Canis::RectTransformComponent);
    REGISTER_COMPONENT_EDITOR(Canis::ColorComponent);
    REGISTER_COMPONENT_EDITOR(Canis::TextComponent);
    REGISTER_COMPONENT_EDITOR(Canis::ButtonComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UIImageComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderComponent);
    REGISTER_COMPONENT_EDITOR(Canis::UISliderKnobComponent);

    // scriptable component
    REGISTER_SCRIPTABLE_COMPONENT(app, DebugCamera2D);
    REGISTER_SCRIPTABLE_COMPONENT(app, SplashLoader);
    REGISTER_SCRIPTABLE_COMPONENT(app, MainMenuButtons);

    // add scene
    app.AddSplashScene(new Canis::Scene("engine_splash", "assets/scenes/engine_splash.scene"));
    app.AddScene(new Canis::Scene("main_menu", "assets/scenes/main_menu.scene"));
    app.AddScene(new Canis::Scene("main_menu_copy", "assets/scenes/main_menu_copy.scene"));

    app.Run("Canis | Stop The Slimes", "main_menu");

    return 0;
}