#pragma once
#include <SDL_keyboard.h>
#include <Canis/InputManager.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>

namespace Canis
{
    struct Line
    {
        glm::vec2 from;
        glm::vec2 to;
    };

    struct Hit2D
    {
        glm::vec2 point; // intersection point
    };

    bool LineIntersection(const Line &_line1, const Line &_line2, Hit2D &_hit)
    {
        glm::vec2 s1 = _line1.to - _line1.from;
        glm::vec2 s2 = _line2.to - _line2.from;

        float s, t;
        float det = -s2.x * s1.y + s1.x * s2.y;

        if (det == 0)
            return false; // lines are parallel

        float invDet = 1 / det;
        glm::vec2 diff = _line1.from - _line2.from;

        s = (-s1.y * diff.x + s1.x * diff.y) * invDet;
        t = (s2.x * diff.y - s2.y * diff.x) * invDet;

        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        {
            // collision detected
            _hit.point = _line1.from + (t * s1);
            return true;
        }

        return false; // no collision
    }
}

class Ball : public Canis::ScriptableEntity
{
private:
    bool m_playing = false;
    float m_speed = 500.0f;
    float m_maxSpeed = 1000000.0f;

    glm::vec2 m_direction;

    const glm::vec2 m_startDirections[4] = {
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, -1.0f),
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(-1.0f, 1.0f)};

    int m_leftScore = 0;
    int m_rightScore = 0;

    Canis::Entity m_leftPaddle;
    Canis::Entity m_rightPaddle;
    Canis::Entity m_leftScoreEntity;
    Canis::Entity m_rightScoreEntity;

public:
    void OnCreate()
    {
        Canis::Log("BALL C");
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
        GetComponent<Canis::RectTransformComponent>().position = glm::vec2(0.0f);

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

    bool LeftWallHit(Canis::RectTransformComponent &_ballRect)
    {
        if (_ballRect.position.x + _ballRect.originOffset.x - (_ballRect.size.x * _ballRect.scale * 0.5f) <= -GetWindow().GetScreenWidth() * 0.5f)
        {
            return true;
        }

        return false;
    }

    bool RightWallHit(Canis::RectTransformComponent &_ballRect)
    {
        if (_ballRect.position.x + _ballRect.originOffset.x + (_ballRect.size.x * _ballRect.scale * 0.5f) >= GetWindow().GetScreenWidth() * 0.5f)
        {
            return true;
        }

        return false;
    }

    bool TopWallHit(Canis::RectTransformComponent &_ballRect)
    {
        if (_ballRect.position.y + _ballRect.originOffset.y + (_ballRect.size.y * _ballRect.scale * 0.5f) >= GetWindow().GetScreenHeight() * 0.5f)
        {
            return true;
        }

        return false;
    }

    bool DownWallHit(Canis::RectTransformComponent &_ballRect)
    {
        if (_ballRect.position.y + _ballRect.originOffset.y - (_ballRect.size.y * _ballRect.scale * 0.5f) <= -GetWindow().GetScreenHeight() * 0.5f)
        {
            return true;
        }

        return false;
    }

    bool HitPaddle(Canis::Entity _paddle, Canis::RectTransformComponent &_ballRect)
    {
        using namespace glm;

        auto paddleRect = _paddle.GetComponent<Canis::RectTransformComponent>();
        vec2 paddlePosition = paddleRect.position + paddleRect.originOffset;
        vec2 ballPosition = _ballRect.position + _ballRect.originOffset;

        float dist = distance(paddlePosition, ballPosition);
        float radius = _ballRect.size.x * 0.5f;

        vec2 betweenPoint = (paddlePosition + ballPosition) * 0.5f;

        // this math is off please fix

        // check if the point is in both the rectangle and circle
        float halfWidth = paddleRect.size.x * paddleRect.scale * 0.5f;
        float halfHeight = paddleRect.size.y * paddleRect.scale * 0.5f;

        if (betweenPoint.x < paddlePosition.x + halfWidth &&
            betweenPoint.x > paddlePosition.x - halfWidth &&
            betweenPoint.y < paddlePosition.y + halfHeight &&
            betweenPoint.y > paddlePosition.y - halfHeight &&
            radius >= distance(betweenPoint, ballPosition))
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
            "Red: " + std::to_string(m_leftScore));

        Canis::Text::Set(
            m_rightScoreEntity.GetComponent<Canis::TextComponent>(),
            m_rightScoreEntity.GetComponent<Canis::RectTransformComponent>(),
            "Blue: " + std::to_string(m_rightScore));
        
        if (m_rightScore >= 3 || m_leftScore >= 3)
        {
            GetSceneManager().Load("main_menu");
        }
    }

    void SpeedBoost(float _multiplier)
    {
        m_speed *= _multiplier;
        m_speed = glm::min(m_speed, m_maxSpeed);
    }

    void OnUpdate(float _dt)
    {
        if (GetInputManager().JustPressedKey(SDLK_SPACE))
        {
            m_playing = true;
        }

        if (m_playing)
        {
            auto &rect = GetComponent<Canis::RectTransformComponent>();
            auto &leftPaddleRect = m_leftPaddle.GetComponent<Canis::RectTransformComponent>();
            auto &rightPaddleRect = m_rightPaddle.GetComponent<Canis::RectTransformComponent>();

            float distanceTraveled = 0.0f;
            float distanceCanTravel = glm::length(m_direction * m_speed * _dt);

            float screenWidth = GetWindow().GetScreenWidth();
            float screenHeight = GetWindow().GetScreenHeight();

            glm::vec2 topLeft(-screenWidth * 0.5f, screenHeight * 0.5f);
            glm::vec2 topRight(screenWidth * 0.5f, screenHeight * 0.5f);
            glm::vec2 bottomLeft(-screenWidth * 0.5f, -screenHeight * 0.5f);
            glm::vec2 bottomRight(screenWidth * 0.5f, -screenHeight * 0.5f);

            Canis::Line leftPaddleLine{
                .from = leftPaddleRect.position + leftPaddleRect.originOffset + glm::vec2(leftPaddleRect.size.x * leftPaddleRect.scale * 0.5f, leftPaddleRect.size.y * leftPaddleRect.scale * 0.5f),
                .to = leftPaddleRect.position + leftPaddleRect.originOffset + glm::vec2(leftPaddleRect.size.x * leftPaddleRect.scale * 0.5f, -leftPaddleRect.size.y * leftPaddleRect.scale * 0.5f)};

            Canis::Line rightPaddleLine{
                .from = rightPaddleRect.position + rightPaddleRect.originOffset + glm::vec2(-rightPaddleRect.size.x, rightPaddleRect.size.y) * rightPaddleRect.scale * 0.5f,
                .to = rightPaddleRect.position + rightPaddleRect.originOffset + glm::vec2(-rightPaddleRect.size.x, -rightPaddleRect.size.y) * rightPaddleRect.scale * 0.5f};

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

            bool didHit = false;
            do
            {
                didHit = false;
                Canis::Line topLine{.from = topLeft, .to = topRight};
                glm::vec2 ballPosition = rect.position + rect.originOffset;
                float ballRadius = rect.size.x * rect.scale * 0.5f;
                Canis::Line ballLine{.from = ballPosition, .to = ballPosition + (glm::normalize(m_direction) * (distanceCanTravel - distanceTraveled + ballRadius))};
                Canis::Hit2D hit;
                if (Canis::LineIntersection(topLine, ballLine, hit))
                {
                    float distanceToHit = glm::distance(ballPosition, hit.point) - ballRadius;

                    distanceTraveled += glm::max(distanceToHit, 0.0f);

                    rect.position += glm::normalize(m_direction) * distanceToHit;

                    m_direction.y = -1.0f;

                    SpeedBoost(1.01f);

                    didHit = true;
                }

                Canis::Line bottomLine{.from = bottomLeft, .to = bottomRight};
                ballPosition = rect.position + rect.originOffset;
                ballLine = {.from = ballPosition, .to = ballPosition + (glm::normalize(m_direction) * (distanceCanTravel - distanceTraveled + ballRadius))};

                if (Canis::LineIntersection(bottomLine, ballLine, hit))
                {
                    float distanceToHit = glm::distance(ballPosition, hit.point) - ballRadius;

                    distanceTraveled += glm::max(distanceToHit, 0.0f);

                    rect.position += glm::normalize(m_direction) * distanceToHit;

                    m_direction.y = 1.0f;

                    SpeedBoost(1.01f);

                    didHit = true;
                }

                Canis::Line leftBarLine{.from = bottomLeft, .to = topLeft};
                ballPosition = rect.position + rect.originOffset;
                ballLine = {.from = ballPosition, .to = ballPosition + (glm::normalize(m_direction) * (distanceCanTravel - distanceTraveled + ballRadius))};

                if (Canis::LineIntersection(leftPaddleLine, ballLine, hit))
                {
                    float distanceToHit = glm::distance(ballPosition, hit.point) - ballRadius;

                    distanceTraveled += glm::max(distanceToHit, 0.0f);

                    rect.position += glm::normalize(m_direction) * distanceToHit;

                    m_direction.x = 1.0f;

                    SpeedBoost(1.01f);

                    didHit = true;
                }

                Canis::Line rigthBarLine{.from = bottomRight, .to = topRight};
                ballPosition = rect.position + rect.originOffset;
                ballLine = {.from = ballPosition, .to = ballPosition + (glm::normalize(m_direction) * (distanceCanTravel - distanceTraveled + ballRadius))};

                if (Canis::LineIntersection(rightPaddleLine, ballLine, hit))
                {
                    float distanceToHit = glm::distance(ballPosition, hit.point) - ballRadius;

                    distanceTraveled += glm::max(distanceToHit, 0.0f);

                    rect.position += glm::normalize(m_direction) * distanceToHit;

                    m_direction.x = -1.0f;

                    SpeedBoost(1.01f);

                    didHit = true;
                }
            } while (distanceTraveled < distanceCanTravel && didHit);

            // if (HitPaddle(m_leftPaddle, rect))
            //{
            //     m_direction.x = 1.0f;
            // }
            // if (HitPaddle(m_rightPaddle, rect))
            //{
            //     m_direction.x = -1.0f;
            // }

            if (distanceTraveled >= distanceCanTravel)
                return;

            if (distanceTraveled == 0.0f)
            {
                rect.position += glm::normalize(m_direction) * m_speed * _dt;
            }
            else
            {
                rect.position += glm::normalize(m_direction) * (distanceCanTravel - distanceTraveled);
            }
        }
    }
};