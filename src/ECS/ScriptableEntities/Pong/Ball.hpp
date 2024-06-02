#pragma once
#include <SDL_keyboard.h>
#include <Canis/InputManager.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/Sprite2DComponent.hpp>

class Ball : public Canis::ScriptableEntity
{
private:
    bool m_playing = false;
    float m_speed = 20.0f;
public:
    void OnCreate()
    {
        Canis::Log("Ball OnCreate");
        
        if (entity.HasComponent<Canis::RectTransformComponent>() == false)
        {
            Canis::FatalError("Ball does not have Canis::RectTransformComponent");
        }
        if (entity.HasComponent<Canis::ColorComponent>() == false)
        {
            Canis::FatalError("Ball does not have Canis::ColorComponent");
        }
        if (entity.HasComponent<Canis::Sprite2DComponent>() == false)
        {
            Canis::FatalError("Ball does not have Canis::Sprite2DComponent");
        }
    }

    void OnReady()
    {

    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        if (GetInputManager().JustPressedKey(SDLK_SPACE))
        {
            Canis::Log("SPACE");
            m_playing = true;
        }

        if (m_playing)
        {
            Canis::Log("MOVE");

            auto& rect = GetComponent<Canis::RectTransformComponent>();

            rect.position.x += m_speed * _dt;
        }
    }
};