#pragma once
#include <Canis/ECS/Systems/ButtonSystem.hpp>

#include <Canis/ECS/Components/IDComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/ButtonComponent.hpp>

#include <Canis/PlayerPrefs.hpp>
#include <Canis/AudioManager.hpp>

#include <SDL_mixer.h>

class MainMenuButtons : public Canis::ScriptableEntity
{
    static void OnClickPlay(Canis::Entity _entity, void *_data)
    {
        Canis::Log("OnClickPlay");
        Canis::AudioManager::Play("assets/audio/sounds/fireball_1.ogg");
        ((MainMenuButtons*)_data)->GetSceneManager().Load("pong");
    }

    static void OnClickPlay3D(Canis::Entity _entity, void *_data)
    {
        Canis::Log("OnClickPlay3D");
        Canis::AudioManager::Play("assets/audio/sounds/fireball_1.ogg");
        ((MainMenuButtons*)_data)->GetSceneManager().Load("mesh");
    }

    static void OnClickSettings(Canis::Entity _entity, void *_data)
    {
        Canis::Log("OnClickPlay");
        Canis::AudioManager::Play("assets/audio/sounds/fireball_1.ogg");
        ((MainMenuButtons*)_data)->GetSceneManager().Load("settings");
    }

    static void OnClickQuit(Canis::Entity _entity, void *_data)
    {
        Canis::Log("OnClickQuit");
        exit(1);
    }
private:
    Canis::ButtonListener playButtonListener;
    Canis::ButtonListener play2dButtonListener;
    Canis::ButtonListener settingsButtonListener;
    Canis::ButtonListener quitButtonListener;
public:

    void OnCreate() {}

    void OnReady()
    {
        // music
        Canis::AudioManager::PlayMusic("assets/audio/music/AlexandrZhelanovSongs/improvisation1.mp3", -1, 0.1f);


        if (Canis::ButtonSystem *buttonSystem = GetScene().GetSystem<Canis::ButtonSystem>())
        {
            playButtonListener = buttonSystem->AddButtonListener("MainMenuPlay", this, OnClickPlay);
            play2dButtonListener = buttonSystem->AddButtonListener("MainMenuPlay3D", this, OnClickPlay3D);
            settingsButtonListener = buttonSystem->AddButtonListener("MainMenuSettings", this, OnClickSettings);
            quitButtonListener = buttonSystem->AddButtonListener("MainMenuQuit", this, OnClickQuit);
        }
    }
    
    void OnDestroy() {}

    void OnUpdate(float _dt) {}


};