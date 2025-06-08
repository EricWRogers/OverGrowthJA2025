#include "Ent.hpp"
#include "../../Components/NPCBoid.hpp"
#include "../../Components/Billboard.hpp"
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/SpriteAnimationComponent.hpp>

void Ent::OnCreate()
{
    // if (!entity.HasComponent<HealthComponent>())
    // {
    //     entity.AddComponent<HealthComponent>();
    // }

    // if (!entity.HasComponent<Canis::SphereCollider>())
    // {
    //     entity.AddComponent<Canis::SphereCollider>();
    // }
    // if (!entity.HasComponent<Billboard>())
    // {
    //     entity.AddComponent<Billboard>();
    // }

    // HealthComponent &health = entity.GetComponent<HealthComponent>();

    // health.maxHealth = 25.0f;

    // Health::ResetHealth(entity);

    // Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    // Canis::SphereCollider &sphere = entity.GetComponent<Canis::SphereCollider>();

    // sphere.layer = (unsigned int)Canis::BIT::THREE;
    // sphere.mask = (unsigned int)Canis::BIT::TWO;

    // m_collisionSystem = GetScene().GetSystem<Canis::CollisionSystem>();
}

void Ent::OnReady()
{
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    if (!entity.HasComponent<Canis::TagComponent>())
    {
        entity.AddComponent<Canis::TagComponent>();
    }

    if (!entity.HasComponent<Canis::SphereCollider>())
    {
        entity.AddComponent<Canis::SphereCollider>();
    }

    if (!entity.HasComponent<Canis::Transform>())
    {
        entity.AddComponent<Canis::Transform>();
    }

    // if (!entity.HasComponent<Canis::Mesh>())
    // {
    //     entity.AddComponent<Canis::Mesh>();
    // }

    if (!entity.HasComponent<Canis::Color>())
    {
        entity.AddComponent<Canis::Color>();
    }

    if (!entity.HasComponent<Billboard>())
    {
        entity.AddComponent<Billboard>();
    }

    if(!entity.HasComponent<NPCBoid>())
    {
        entity.AddComponent<NPCBoid>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = 25.0f;

    Health::ResetHealth(entity);
    //Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    entity.SetTag("ENT");

    Canis::Transform &transform = entity.GetComponent<Canis::Transform>();
    transform.position = glm::vec3(0.0f);
    transform.rotation = glm::vec3(0.0f);

    Canis::SphereCollider &sphere = entity.GetComponent<Canis::SphereCollider>();

    sphere.layer = (unsigned int)Canis::BIT::THREE;
    sphere.mask = (unsigned int)Canis::BIT::TWO;

    m_collisionSystem = GetScene().GetSystem<Canis::CollisionSystem>();

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    m_wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void Ent::OnUpdate(float _dt)
{
    
}

void Ent::Attack()
{
    // std::vector<entt::entity> targets = m_collisionSystem->GetHits(entity);
    // for (entt::entity id : targets)
    // {
    //     Canis::Entity enemy(id, &GetScene());
    //     HealthComponent &attackersHealth = enemy.GetComponent<HealthComponent>();
    //     Health::Damage(enemy, damage);
    //     Canis::Log("Current is " + std::to_string(attackersHealth.currentHealth));
    // }
}

void Ent::MoveToAttack()
{
    //Canis::Log("Enemies Have Been Spotted Defend");
    // if (m_path.size() == 0)
    // {
    //     m_index = 0;

    //     int idFrom = m_wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
    //     int idTo = 0;

    //     std::vector<Canis::Entity> enemies = entity.GetEntitiesWithTag("ENEMY");
    //     float closestDistance = std::numeric_limits<float>::max();
    //     glm::vec3 npcPos = entity.GetGlobalPosition();

    //     for (Canis::Entity &enemy : enemies)
    //     {
    //         float dist = glm::distance(enemy.GetGlobalPosition(), npcPos);
    //         if (dist < closestDistance)
    //         {
    //             closestDistance = dist;
    //             idTo = m_wavePointsManager->aStar.GetClosestPoint(enemy.GetGlobalPosition());
    //         }
    //     }

    //     m_path = m_wavePointsManager->aStar.GetPath(idFrom, idTo);

    //     if (m_path.empty())
    //     {
    //         return;
    //     }
    // }

    // if (m_index >= m_path.size())
    // {
    //     m_path.clear();
    //     return;
    // }

    // entity.GetComponent<NPCBoid>().target = m_path[m_index];

    // if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
    // {
    //     m_index++;
    // }
}

void Ent::Roam()
{
    // Canis::Log("Nothing going on here");
    // if (m_path.empty())
    // {
    //     m_index = 0;

    //     glm::vec3 currentPos = entity.GetGlobalPosition();
    //     int idFrom = m_wavePointsManager->aStar.GetClosestPoint(currentPos);

    //     if (idFrom == 0)
    //     {
    //         Canis::Log("Skipping Roam.");
    //         return;
    //     }

    //     std::vector<int> nearbyNodeIDs;
    //     float roamRadius = 5.0f;

    //     // Try random directions around the entity
    //     for (int i = 0; i < 20; ++i) // 20 random samples
    //     {
    //         float angle = glm::radians((float)(rand() % 360));
    //         glm::vec3 offset = glm::vec3(cos(angle), 0.0f, sin(angle)) * roamRadius * ((rand() % 100) / 100.0f);
    //         glm::vec3 samplePos = currentPos + offset;

    //         if (!m_wavePointsManager->aStar.ValidPoint(samplePos))
    //         {
    //             continue;
    //         }

    //         int id = m_wavePointsManager->aStar.GetClosestPoint(samplePos);

    //         if (id != idFrom)
    //         {
    //             nearbyNodeIDs.push_back(id);
    //         }
    //     }

    //     if (nearbyNodeIDs.empty())
    //     {
    //         return;
    //     }

    //     int idTo = nearbyNodeIDs[rand() % nearbyNodeIDs.size()];
    //     m_path = m_wavePointsManager->aStar.GetPath(idFrom, idTo);

    //     if (m_path.empty())
    //     {
    //         return;
    //     }
    // }

    // if (m_index >= m_path.size())
    // {
    //     return;
    // }

    // entity.GetComponent<NPCBoid>().target = m_path[m_index];

    // if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
    // {
    //     m_index++;
    // }
}