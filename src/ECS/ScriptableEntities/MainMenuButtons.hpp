#pragma once

#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>
#include <Canis/ECS/Components/ButtonComponent.hpp>

#include "../../Scripts/TileMap.hpp"

class MainMenuButtons : public Canis::ScriptableEntity
{
    static void OnClickPlay(void *instance)
    {
        ((MainMenuButtons * )instance)->GetAssetManager().Get<Canis::SoundAsset>(((MainMenuButtons * )instance)->GetAssetManager().LoadSound("assets/audio/sounds/click1.wav"))->Play();
        ((Canis::SceneManager *)((MainMenuButtons * )instance)->m_Entity.scene->sceneManager)->Load("demo");
    }

    static void OnClickQuit(void *instance)
    {
        exit(1);
    }
public:
    int kennyPixelSquareFontId, kennyBlocksFontId = 0;

    void OnCreate()
    {
        
    }

    void OnReady()
    {
        // load font
        kennyPixelSquareFontId = GetAssetManager().LoadText("assets/fonts/KenneyFonts/Fonts/KenneyPixelSquare.ttf",48);
        kennyBlocksFontId = GetAssetManager().LoadText("assets/fonts/KenneyFonts/Fonts/KenneyBlocks.ttf",48);
        // music
        GetAssetManager().Get<Canis::MusicAsset>(GetAssetManager().LoadMusic("assets/audio/music/AlexandrZhelanovSongs/improvisation1.mp3"))->Play(-1);

        { // build version text
            Canis::Entity text = CreateEntity();
            text.AddComponent<Canis::RectTransformComponent>(
                true,                                                   // active
                Canis::RectAnchor::BOTTOMRIGHT,
                glm::vec2(-15.0f, 40.0f),  // position
                glm::vec2(0.0f, 0.0f),                                  // size
                glm::vec2(0.0f, 0.0f),                                  // originOffset
                0.0f,                                                   // rotation
                0.4f,                                                   // scale
                0.0f                                                    // depth
            );
            text.AddComponent<Canis::ColorComponent>(
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
            );
            text.AddComponent<Canis::TextComponent>(
                kennyPixelSquareFontId,
                new std::string("Prototype Build Version : " + gameConfig.gameVersion), // text
                1u
            );
        }

        { // asset version text
            Canis::Entity text = CreateEntity();
            text.AddComponent<Canis::RectTransformComponent>(
                true,                                                   // active
                Canis::RectAnchor::BOTTOMRIGHT,
                glm::vec2(-15.0f, 15.0f),  // position
                glm::vec2(0.0f, 0.0f),                                  // size
                glm::vec2(0.0f, 0.0f),                                  // originOffset
                0.0f,                                                   // rotation
                0.4f,                                                   // scale
                0.0f                                                    // depth
            );
            text.AddComponent<Canis::ColorComponent>(
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
            );
            text.AddComponent<Canis::TextComponent>(
                kennyPixelSquareFontId,
                new std::string("Prototype Asset Version : " + gameConfig.assetVersion), // text
                1u
            );
        }

        { // title text
            Canis::Entity text = CreateEntity();
            text.AddComponent<Canis::RectTransformComponent>(
                true,                                                   // active
                Canis::RectAnchor::TOPCENTER,
                glm::vec2(-200.0f, -200.0f),  // position
                glm::vec2(0.0f, 0.0f),                                  // size
                glm::vec2(0.0f, 0.0f),                                  // originOffset
                0.0f,                                                   // rotation
                1.0f,                                                   // scale
                0.0f                                                    // depth
            );
            text.AddComponent<Canis::ColorComponent>(
                glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) // #26854c
            );
            text.AddComponent<Canis::TextComponent>(
                kennyPixelSquareFontId,
                new std::string("Stop The Slimes") // text
            );
        }

        Canis::Entity playButton = CreateEntity();
        auto& playRect = playButton.AddComponent<Canis::RectTransformComponent>(
            true,                                                // active
            Canis::RectAnchor::CENTERLEFT,
            glm::vec2(200.0f, 50.0f), // position
            glm::vec2(150.0f, 40.0f),                               // size
            glm::vec2(0.0f, 0.0f),                                  // originOffset
            0.0f,                                                   // rotation
            1.0f,                                                // scale
            0.0f 
        );
        auto& playColor = playButton.AddComponent<Canis::ColorComponent>(
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
        );
        auto& playText = playButton.AddComponent<Canis::TextComponent>(
            GetAssetManager().LoadText("assets/fonts/Antonio-Bold.ttf", 48),
            new std::string("Play"), // text
            0u
        );
        auto& playB = playButton.AddComponent<Canis::ButtonComponent>(
            OnClickPlay,
            this,
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec4(0.24f, 0.37f, 0.25f, 1.0f) //Green, #3c5e40
        );

        Canis::Entity quitButton = CreateEntity();
        auto& quitRect = quitButton.AddComponent<Canis::RectTransformComponent>(
            true,                                                // active
            Canis::RectAnchor::CENTERLEFT,
            glm::vec2(200.0f, -50.0f), // position
            glm::vec2(150.0f, 40.0f),                               // size
            glm::vec2(0.0f, 0.0f),                                  // originOffset
            0.0f,                                                   // rotation
            1.0f,                                                // scale
            0.0f 
        );
        auto& quitColor = quitButton.AddComponent<Canis::ColorComponent>(
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
        );
        auto& quitText = quitButton.AddComponent<Canis::TextComponent>(
            GetAssetManager().LoadText("assets/fonts/Antonio-Bold.ttf", 48),
            new std::string("Quit"), // text
            0u
        );
        auto& quitB = quitButton.AddComponent<Canis::ButtonComponent>(
            OnClickQuit,
            this,
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
        );
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