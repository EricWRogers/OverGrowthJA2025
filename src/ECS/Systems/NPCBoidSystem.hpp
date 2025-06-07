#pragma once

#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include <Canis/ECS/Systems/System.hpp>
#include <Canis/ECS/Systems/CollisionSystem.hpp>

class NPCBoidSystem : public Canis::System
{
private:
    Canis::CollisionSystem *m_collisionSystem = nullptr;

    const float MAX_ALIGNMENT_DISTANCE = 1.5f;
    const float MAX_COHESION_DISTANCE = 2.0f;
    const float MAX_SEPARATION_DISTANCE = 0.9f;

    const float USER_BEHAVIOR_WEIGHT = 2.5f;
    const float SEPARATION_WEIGHT = 1.0f;
    const float ALIGNMENT_WEIGHT = 0.4f;
    const float COHESION_WEIGHT = 0.15f;

    const float DRAG = 0.95f;
    const float MAXSPEED = 60.0f;

    glm::vec2 Seek(glm::vec2 _agentPosition, glm::vec2 _targetPosition);
    glm::vec2 Flee(glm::vec2 _agentPosition, glm::vec2 _targetPosition);
    glm::vec2 Alignment(entt::entity _agent, glm::vec2 _agentPosition, entt::registry &_registry);
    glm::vec2 Cohesion(entt::entity _agent, glm::vec2 _agentPosition, entt::registry &_registry);
    glm::vec2 Separation(entt::entity _agent, glm::vec2 _agentPosition, entt::registry &_registry);

public:
    NPCBoidSystem() : Canis::System() { m_name = type_name<NPCBoidSystem>(); }

    void Create();
    void Ready();
    void Update(entt::registry &_registry, float _deltaTime);
};

static bool DecodeNPCBoidSystem(const std::string &_name, Canis::Scene *_scene)
{
    if (_name == "NPCBoidSystem")
    {
        _scene->CreateSystem<NPCBoidSystem>();
        return true;
    }
    return false;
}