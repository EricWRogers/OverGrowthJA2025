#pragma once
#include <Canis/ECS/Systems/ButtonSystem.hpp>

#include <Canis/ECS/Components/IDComponent.hpp>
#include <Canis/ECS/Components/Color.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/ButtonComponent.hpp>

#include <Canis/PlayerPrefs.hpp>
#include <Canis/AudioManager.hpp>

#include <SDL_mixer.h>
#include "../Player/PlayerBuildInput.hpp"

class BuildMenu : public Canis::ScriptableEntity
{

    //Actual functionality.
    static void OnClickBuildHut(Canis::Entity _entity, void *_data)
    {
        Canis::Log("Clicked Build Hut");
        _entity.GetEntityWithTag("PLAYERBUILDINPUT").GetScript<PlayerBuildInput>().currentType = PlayerBuildInput::Hut;
       
        
    }

    static void OnClickBuildBarracks(Canis::Entity _entity, void *_data)
    {
        Canis::Log("Clicked Build Barracks");
        _entity.GetEntityWithTag("PLAYERBUILDINPUT").GetScript<PlayerBuildInput>().currentType = PlayerBuildInput::Barracks;
        
       
    }

    static void OnClickBuildFarm(Canis::Entity _entity, void *_data)
    {
        Canis::Log("Clicked Build Farm");
        _entity.GetEntityWithTag("PLAYERBUILDINPUT").GetScript<PlayerBuildInput>().currentType = PlayerBuildInput::Farm;
        
      
    }

    static void OnClickBuildWoodHut(Canis::Entity _entity, void *_data)
    {
        Canis::Log("Clicked Build Wood Hut");
        _entity.GetEntityWithTag("PLAYERBUILDINPUT").GetScript<PlayerBuildInput>().currentType = PlayerBuildInput::WoodHut;
    }
private:
    Canis::ButtonListener buildHutListener;
    Canis::ButtonListener buildBarracksListener;
    Canis::ButtonListener buildFarmListener;
    Canis::ButtonListener buildWoodHutListener;
public:

    void OnCreate() {}

    void OnReady()
    {
        // Replace with wound effect.
        //Canis::AudioManager::PlayMusic("assets/audio/music/AlexandrZhelanovSongs/improvisation1.mp3", -1, 0.1f);


        if (Canis::ButtonSystem *buttonSystem = GetScene().GetSystem<Canis::ButtonSystem>()) //If button system is in the scene.
        {
            //Apply Listeners
            buildHutListener = buttonSystem->AddButtonListener("BuildHut", this, OnClickBuildHut);
            buildBarracksListener = buttonSystem->AddButtonListener("BuildBarracks", this, OnClickBuildBarracks);
            buildFarmListener = buttonSystem->AddButtonListener("BuildFarm", this, OnClickBuildFarm);
            buildWoodHutListener = buttonSystem->AddButtonListener("BuildWoodHut", this, OnClickBuildWoodHut);
        }
    }
    
    void OnDestroy() {}

    void OnUpdate(float _dt) {}


};
