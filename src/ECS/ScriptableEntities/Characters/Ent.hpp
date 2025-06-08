#pragma once

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Systems/CollisionSystem.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>
#include <Canis/ECS/Components/Transform.hpp>
#include <Canis/ECS/Components/TagComponent.hpp>
#include <Canis/ECS/Components/Mesh.hpp>
#include <Canis/ECS/Components/Color.hpp>
#include "WavePointsManager.hpp"
#include "../../Components/Health.hpp"

class Ent : public Canis::ScriptableEntity
{
private:
    WavePointsManager* m_wavePointsManager;
    Canis::CollisionSystem* m_collisionSystem;
    std::vector<glm::vec3> m_path = {};
    std::vector<std::string> m_tags = {};
    float m_counter = 0.0f;
    float m_waitTime = 2.0f;
    int m_index = 0;
    bool m_enemyWaveStarted = false;
public:
    float damage = 2.0f;

    void OnCreate();

    void OnReady();

    void OnDestroy() {}

    void OnUpdate(float _dt);

    void Attack();

    void MoveToAttack();

    void Roam();
};