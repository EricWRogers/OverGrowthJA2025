#include "NPCBoidSystem.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Canis/ECS/Components/Transform.hpp>
#include <Canis/ECS/Components/Color.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>
#include <Canis/ECS/Components/ParticleEmitter.hpp>
#include <Canis/ECS/Components/Mesh.hpp>

#include "../Components/NPCBoid.hpp"

using namespace Canis;

glm::vec2 NPCBoidSystem::Seek(glm::vec2 _agentPosition, glm::vec2 _targetPosition)
{
    glm::vec2 seek = _targetPosition - _agentPosition;
    return glm::normalize(seek);
}

glm::vec2 NPCBoidSystem::Flee(glm::vec2 _agentPosition, glm::vec2 _targetPosition)
{
    glm::vec2 seek = _agentPosition - _targetPosition;
    return glm::normalize(seek);
}

glm::vec2 NPCBoidSystem::Alignment(entt::entity _agent, glm::vec2 _agentPosition, entt::registry &_registry)
{
    glm::vec2 alignment = glm::vec2(0.0f);
    int numNeighbors = 0;

    auto view = _registry.view<Transform, NPCBoid>();
    for (auto [entity, transform, boid] : view.each())
    {
        if (_agent != entity)
        {
            vec3 boidPosition = GetGlobalPosition(transform);
            if (glm::distance(_agentPosition, vec2(boidPosition.x, boidPosition.z)) <= MAX_ALIGNMENT_DISTANCE)
            {
                numNeighbors++;
                alignment += boid.velocity;
            }
        }
    }

    if (alignment != glm::vec2(0.0f))
    {
        return glm::normalize(alignment / (numNeighbors + 0.0f));
    }

    return glm::vec2(0.0f);
}

glm::vec2 NPCBoidSystem::Cohesion(entt::entity _agent, glm::vec2 _agentPosition, entt::registry &_registry)
{
    glm::vec2 cohesion = glm::vec2(0.0f);
    int numNeighbors = 0;

    auto view = _registry.view<Transform, NPCBoid>();
    for (auto [entity, transform, bird] : view.each())
    {
        if (_agent != entity)
        {
            vec3 boidPosition = GetGlobalPosition(transform);
            if (glm::distance(_agentPosition, vec2(boidPosition.x, boidPosition.z)) <= MAX_COHESION_DISTANCE)
            {
                numNeighbors++;
                cohesion += vec2(boidPosition.x, boidPosition.z);
            }
        }
    }

    if (numNeighbors == 0)
        return glm::vec2(0.0f);

    cohesion /= numNeighbors;

    if (cohesion - _agentPosition == glm::vec2(0.0f))
        return glm::vec2(0.0f);

    return glm::normalize((cohesion - _agentPosition));
}

glm::vec2 NPCBoidSystem::Separation(entt::entity _agent, glm::vec2 _agentPosition, entt::registry &_registry)
{
    glm::vec2 separation = glm::vec2(0.0f);
    int numNeighbors = 0;

    auto view = _registry.view<Transform, NPCBoid>();
    for (auto [entity, transform, bird] : view.each())
    {
        if (_agent != entity)
        {
            vec3 boidPosition = GetGlobalPosition(transform);
            if (glm::distance(_agentPosition, vec2(boidPosition.x, boidPosition.z)) <= MAX_SEPARATION_DISTANCE)
            {
                numNeighbors++;
                separation += (_agentPosition - vec2(boidPosition.x, boidPosition.z));
            }
        }
    }

    if (separation != glm::vec2(0.0f))
    {
        return glm::normalize(separation);
    }

    return glm::vec2(0.0f);
}

void NPCBoidSystem::Create()
{
}

void NPCBoidSystem::Ready()
{
    m_collisionSystem = scene->GetSystem<Canis::CollisionSystem>();
}

void NPCBoidSystem::Update(entt::registry &_registry, float _deltaTime)
{
    auto view = _registry.view<Transform, NPCBoid>();

    for (auto [id, transformBird, boid] : view.each())
    {
        Canis::Entity entity(id, scene);
        vec3 birdPos = entity.GetGlobalPosition();
        vec2 pos = vec2(birdPos.x, birdPos.z);

        // calculate directions
        vec2 seekTarget = Seek(pos, vec2(boid.target.x, boid.target.z));
        vec2 alignmentTarget = Alignment(entity, pos, _registry);
        vec2 cohesionTarget = Cohesion(entity, pos, _registry);
        vec2 separationTarget = Separation(entity, pos, _registry);

        boid.acceleration = (seekTarget * USER_BEHAVIOR_WEIGHT) +
                            (alignmentTarget * ALIGNMENT_WEIGHT) +
                            (cohesionTarget * COHESION_WEIGHT) +
                            (separationTarget * SEPARATION_WEIGHT);

        float yRotation = atan2(boid.velocity.x, boid.velocity.y);

        SetTransformRotation(transformBird, vec3(0.0f, yRotation + (180.0f * DEG2RAD), 0.0f));

        // update velocity
        boid.velocity += boid.acceleration;

        // clamp velocity to maxSpeed
        if (glm::length(boid.velocity) > boid.maxSpeed)
        {
            boid.velocity = normalize(boid.velocity);
            boid.velocity *= boid.maxSpeed;
        }

        // apply drag
        boid.velocity *= boid.drag;

        // update position
        pos += boid.velocity * _deltaTime;

        SetGlobalPosition(transformBird, vec3(pos.x, GetGlobalPosition(transformBird).y, pos.y));
    }
}