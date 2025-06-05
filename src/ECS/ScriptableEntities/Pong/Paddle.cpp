#include "Paddle.hpp"

#include <SDL_keyboard.h>
#include <Canis/InputManager.hpp>
#include <Canis/ECS/Components/TagComponent.hpp>
#include <Canis/ECS/Components/RectTransform.hpp>
#include <Canis/ECS/Components/Color.hpp>
#include <Canis/ECS/Components/Sprite2DComponent.hpp>

void Paddle::OnCreate()
{        
    if (entity.HasComponent<Canis::RectTransform>() == false)
    {
        Canis::FatalError("Paddle does not have Canis::RectTransform");
    }
    if (entity.HasComponent<Canis::Color>() == false)
    {
        Canis::FatalError("Paddle does not have Canis::Color");
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

    vec2 dir(0.0f);

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

    auto& rect = GetComponent<Canis::RectTransform>();
    rect.position.y += dir.y * m_speed * _dt;
}