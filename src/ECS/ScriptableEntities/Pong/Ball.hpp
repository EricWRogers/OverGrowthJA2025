#pragma once

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>


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
    void OnCreate();

    void ResetBall();

    void OnReady();

    void OnDestroy() {}

    bool LeftWallHit(Canis::RectTransformComponent &_ballRect);

    bool RightWallHit(Canis::RectTransformComponent &_ballRect);

    bool TopWallHit(Canis::RectTransformComponent &_ballRect);

    bool DownWallHit(Canis::RectTransformComponent &_ballRect);

    bool HitPaddle(Canis::Entity _paddle, Canis::RectTransformComponent &_ballRect);

    void UpdateScoreText();

    void SpeedBoost(float _multiplier);

    void OnUpdate(float _dt);
};