#pragma once
#include <Canis/ECS/Systems/ButtonSystem.hpp>

#include <Canis/ECS/Components/IDComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/ButtonComponent.hpp>
#include <Canis/ECS/Components/UISliderKnobComponent.hpp>

#include <Canis/Canis.hpp>
#include <Canis/PlayerPrefs.hpp>
#include <Canis/AudioManager.hpp>

#include <SDL_mixer.h>

class SettingsMenuFunctions : public Canis::ScriptableEntity
{
    static void OnClickMainMenu(Canis::Entity _entity, void *_data)
    {
        Canis::Log("OnClickPlay");
        Canis::AudioManager::Play("assets/audio/sounds/fireball_1.ogg");
        ((SettingsMenuFunctions*)_data)->GetSceneManager().Load("main_menu");
    }

    static void OnAudioSliderChanged(Canis::Entity _entity, float _value, void *_data)
    {
        Canis::GetProjectConfig().volume = _value;
        Canis::AudioManager::UpdateMusicVolume();
        Canis::PlayerPrefs::SetInt( "master_volume", (int)(_value * 128));
    }
private:
    Canis::KnobListener knobHandle;
    Canis::ButtonListener mainMenuButtonListener;
public:

    void OnCreate() {}

    void OnReady()
    {
        // music
        Canis::AudioManager::PlayMusic("assets/audio/music/AlexandrZhelanovSongs/improvisation1.mp3", -1, 0.1f);

        Canis::ButtonSystem *buttonSystem = GetScene().GetSystem<Canis::ButtonSystem>();
        mainMenuButtonListener = buttonSystem->AddButtonListener("Main_Menu_Button", this, OnClickMainMenu);

        Canis::UISliderKnobSystem *knobSystem = GetScene().GetSystem<Canis::UISliderKnobSystem>();
        knobHandle = knobSystem->AddKnobListener("MASTER_VOLUME_SLIDER_CHANGED", this, OnAudioSliderChanged);

        Canis::Entity knob = entity.GetEntityWithTag("MasterVolumeKnob");
        knob.GetComponent<Canis::UISliderKnobComponent>().value = Canis::GetProjectConfig().volume;
    }
    
    void OnDestroy() {}

    void OnUpdate(float _dt) {}


};