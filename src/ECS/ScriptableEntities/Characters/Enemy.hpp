#pragma once

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Systems/CollisionSystem.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>
#include "../../Components/Health.hpp"
#include "WavePointsManager.hpp"

class Enemy : public Canis::ScriptableEntity
{
private:
    WavePointsManager* m_wavePointsManager;
    std::vector<glm::vec3> m_path = {};
    float m_counter = 0.0f;
    float m_waitTime = 2.0f;
    int m_index = 0;
    bool m_isEntsAlive = false;
    Canis::CollisionSystem* m_collisionSystem;
public:
    float damage = 5.0f;
    std::string animationName = "";

    void OnCreate();
    
    void OnReady();
    
    void OnDestroy() {}

    void OnUpdate(float _dt);

    void Attack();

    void GoTo();

    void SetAnimation(std::string _path, bool _flipX);
};