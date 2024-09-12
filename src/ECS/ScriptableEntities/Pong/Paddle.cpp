#include "Paddle.hpp"

#include <SDL_keyboard.h>
#include <Canis/InputManager.hpp>
#include <Canis/ECS/Components/TagComponent.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/Sprite2DComponent.hpp>

void Paddle::OnCreate()
{        
    if (entity.HasComponent<Canis::RectTransformComponent>() == false)
    {
        Canis::FatalError("Paddle does not have Canis::RectTransformComponent");
    }
    if (entity.HasComponent<Canis::ColorComponent>() == false)
    {
        Canis::FatalError("Paddle does not have Canis::ColorComponent");
    }
    if (entity.HasComponent<Canis::Sprite2DComponent>() == false)
    {
        Canis::FatalError("Paddle does not have Canis::Sprite2DComponent");
    }

    left = entity.TagEquals("LEFT_PADDLE");
    right = !left;
}

void Paddle::OnUpdate(float _dt)
{
    using namespace glm;

    vec2 dir;

    if (left)
    {
        dir.y += GetInputManager().GetKey(SDL_SCANCODE_W);
        dir.y += GetInputManager().GetKey(SDL_SCANCODE_S) * -1;
    }

    if (right)
    {
        dir.y += GetInputManager().GetKey(SDL_SCANCODE_UP);
        dir.y += GetInputManager().GetKey(SDL_SCANCODE_DOWN) * -1;
    }

    auto& rect = GetComponent<Canis::RectTransformComponent>();
    rect.position.y += dir.y * m_speed * _dt;
}