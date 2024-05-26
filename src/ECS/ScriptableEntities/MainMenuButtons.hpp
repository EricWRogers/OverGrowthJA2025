#pragma once
#include <Canis/ECS/Systems/ButtonSystem.hpp>

#include <Canis/ECS/Components/IDComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/ButtonComponent.hpp>

#include <Canis/AudioManager.hpp>

class MainMenuButtons : public Canis::ScriptableEntity
{
    static void OnClickPlay(Canis::Entity _entity, void *_data)
    {
        Canis::Log("OnClickPlay");
        Canis::AudioManager::Play("assets/audio/sounds/click1.wav");
        ((MainMenuButtons*)_data)->GetSceneManager().Load("demo");
    }

    static void OnClickQuit(Canis::Entity _entity, void *_data)
    {
        Canis::Log("OnClickQuit");
        exit(1);
    }

    static void OnAudioSliderChanged(Canis::Entity _entity, float _value, void *_data)
    {
        Canis::Log("OnAudioSliderChanged");
    }
private:
    Canis::KnobListener knobHandle;
    Canis::ButtonListener playButtonListener;
    Canis::ButtonListener quitButtonListener;
public:
    int kennyPixelSquareFontId, kennyBlocksFontId = 0;

    void OnCreate()
    {
        Canis::Log("OnCreate");
    }

    void OnReady()
    {
        Canis::ButtonSystem *buttonSystem = GetScene().GetSystem<Canis::ButtonSystem>();

        playButtonListener = buttonSystem->AddButtonListener("MainMenuPlay", this, OnClickPlay);
        quitButtonListener = buttonSystem->AddButtonListener("MainMenuQuit", this, OnClickQuit);

        Canis::UISliderKnobSystem *knobSystem = GetScene().GetSystem<Canis::UISliderKnobSystem>();

        knobHandle = knobSystem->AddKnobListener("VolumeSliderChanged", this, OnAudioSliderChanged);
    }
    
    void OnDestroy()
    {
        
    }

    void OnUpdate(float _dt)
    {
        
    }


};

bool DecodeMainMenuButtons(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "MainMenuButtons")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<MainMenuButtons>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}

bool EncodeMainMenuButtons(YAML::Emitter &_out, Canis::ScriptableEntity* _scriptableEntity)
{
    if ((_scriptableEntity = dynamic_cast<MainMenuButtons*>(_scriptableEntity)) != nullptr)
    {
        _out << YAML::Key << "Canis::ScriptComponent" << YAML::Value << "MainMenuButtons";
        return true;
    }

    return false;
}