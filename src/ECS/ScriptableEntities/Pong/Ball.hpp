#pragma once
#include <SDL_keyboard.h>
#include <Canis/InputManager.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>


class Ball : public Canis::ScriptableEntity
{
private:
    bool m_playing = false;
    float m_speed = 300.0f;

    glm::vec2 m_direction;

    const glm::vec2 m_startDirections[4] = {
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, -1.0f),
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(-1.0f, 1.0f)
    };

    int m_leftScore = 0;
    int m_rightScore = 0;

    Canis::Entity m_leftPaddle;
    Canis::Entity m_rightPaddle;
    Canis::Entity m_leftScoreEntity;
    Canis::Entity m_rightScoreEntity;
public:
    void OnCreate()
    {
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

    void ResetBall()
    {
        // stop movement
        m_playing = false;

        // reset position to center of the screen
        GetComponent<Canis::RectTransformComponent>().position =  glm::vec2(0.0f);

        // reset position of the paddles
        m_leftPaddle.GetComponent<Canis::RectTransformComponent>().position.y = 0.0f;
        m_rightPaddle.GetComponent<Canis::RectTransformComponent>().position.y = 0.0f;

        // pick random direction
        m_direction = m_startDirections[rand() % 4];

        UpdateScoreText();
    }

    void OnReady()
    {
        m_leftPaddle = entity.GetEntityWithTag("LEFT_PADDLE");
        m_rightPaddle = entity.GetEntityWithTag("RIGHT_PADDLE");
        m_leftScoreEntity = entity.GetEntityWithTag("RED_SCORE");
        m_rightScoreEntity = entity.GetEntityWithTag("BLUE_SCORE");

        ResetBall();
    }
    
    void OnDestroy()
    {

    }

    bool LeftWallHit(Canis::RectTransformComponent& _ballRect)
    {
        if (_ballRect.position.x + _ballRect.originOffset.x - (_ballRect.size.x * _ballRect.scale * 0.5f) <= -GetWindow().GetScreenWidth() * 0.5f )
        {
            return true;
        }

        return false;
    }

    bool RightWallHit(Canis::RectTransformComponent& _ballRect)
    {
        if (_ballRect.position.x + _ballRect.originOffset.x + (_ballRect.size.x * _ballRect.scale * 0.5f) >= GetWindow().GetScreenWidth() * 0.5f )
        {
            return true;
        }

        return false;
    }

    bool TopWallHit(Canis::RectTransformComponent& _ballRect)
    {
        if (_ballRect.position.y + _ballRect.originOffset.y + (_ballRect.size.y * _ballRect.scale * 0.5f) >= GetWindow().GetScreenHeight() * 0.5f )
        {
            return true;
        }

        return false;
    }

    bool DownWallHit(Canis::RectTransformComponent& _ballRect)
    {
        if (_ballRect.position.y + _ballRect.originOffset.y - (_ballRect.size.y * _ballRect.scale * 0.5f) <= -GetWindow().GetScreenHeight() * 0.5f )
        {
            return true;
        }

        return false;
    }

    bool HitPaddle(Canis::Entity _paddle, Canis::RectTransformComponent& _ballRect)
    {
        using namespace glm;

        auto paddleRect = _paddle.GetComponent<Canis::RectTransformComponent>();
        vec2 paddlePosition = paddleRect.position + paddleRect.originOffset;

        float dist = distance( paddlePosition, _ballRect.position + _ballRect.originOffset);
        float radius = _ballRect.size.x * 0.5f;

        vec2 betweenPoint = ( paddlePosition + (_ballRect.position + _ballRect.originOffset) ) * 0.5f;

        // this math is off please fix

        // check if the point is in both the rectangle and circle
        float halfWidth = paddleRect.size.x * paddleRect.scale * 0.5f;
        float halfHeight = paddleRect.size.y * paddleRect.scale * 0.5f;

        if (betweenPoint.x < paddlePosition.x + halfWidth &&
            betweenPoint.x > paddlePosition.x - halfWidth &&
            betweenPoint.y < paddlePosition.y + halfHeight &&
            betweenPoint.y > paddlePosition.y - halfHeight &&
            radius > distance( betweenPoint, _ballRect.position + _ballRect.originOffset))
        {
            return true; // hit
        }


        return false;
    }

    void UpdateScoreText()
    {
        Canis::Text::Set(
            m_leftScoreEntity.GetComponent<Canis::TextComponent>(),
            m_leftScoreEntity.GetComponent<Canis::RectTransformComponent>(),
            "Red: " + std::to_string(m_leftScore)
        );

        Canis::Text::Set(
            m_rightScoreEntity.GetComponent<Canis::TextComponent>(),
            m_rightScoreEntity.GetComponent<Canis::RectTransformComponent>(),
            "Blue: " + std::to_string(m_rightScore)
        );
    }

    void OnUpdate(float _dt)
    {
        if (GetInputManager().JustPressedKey(SDLK_SPACE))
        {
            m_playing = true;
        }

        if (m_playing)
        {
            auto& rect = GetComponent<Canis::RectTransformComponent>();

            if (LeftWallHit(rect))
            {
                m_rightScore++;
                ResetBall();
                return;
            }

            if (RightWallHit(rect))
            {
                m_leftScore++;
                ResetBall();
                return;
            }

            if (TopWallHit(rect))
            {
                m_direction.y = -1.0f;
            }

            if (DownWallHit(rect))
            {
                m_direction.y = 1.0f;
            }

            if (HitPaddle(m_leftPaddle, rect))
            {
                m_direction.x = 1.0f;
                m_speed *= 1.2f;
            }

            if (HitPaddle(m_rightPaddle, rect))
            {
                m_direction.x = -1.0f;
            }

            rect.position += m_direction * m_speed * _dt;
        }
    }
};