#include "Enemy.hpp"
#include "../../Components/NPCBoid.hpp"

void Enemy::OnCreate()
{
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = 25.0f;

    Health::ResetHealth(entity);

    Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    Canis::SphereCollider &sphere = entity.GetComponent<Canis::SphereCollider>();

    sphere.layer = (unsigned int)Canis::BIT::TWO;
    sphere.mask = (unsigned int)Canis::BIT::THREE;

    m_collisionSystem = GetScene().GetSystem<Canis::CollisionSystem>();
}

void Enemy::OnReady()
{
    entity.AddComponent<NPCBoid>();

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    m_wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void Enemy::OnUpdate(float _dt)
{
    GoTo();
}

void Enemy::Attack(Canis::Entity _target)
{
    if(m_isEntsAlive)
    {
        Canis::Entity closestEnt = GetClosestEnt();

        // entt::entity is the id of Canis::Entity
        std::vector<entt::entity> targets = m_collisionSystem->GetHits(entity);
        for (entt::entity id : targets)
        {
            Canis::Entity ent(id, &GetScene());
            

        }
    }
}

void Enemy::GoTo()
{
    if (m_path.size() == 0)
    {
        m_index = 0;

        int idFrom = m_wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
        int idTo = 0;

        std::vector<Canis::Entity> ents = entity.GetEntitiesWithTag("ENT");

        if(ents.size() == 0)
        {
            m_isEntsAlive = false;
        }else
        {
            m_isEntsAlive = true;
        }

        if (m_isEntsAlive)
        {
            float closestDistance = std::numeric_limits<float>::max();
            glm::vec3 npcPos = entity.GetGlobalPosition();

            for (Canis::Entity &ent : ents)
            {
                float dist = glm::distance(ent.GetGlobalPosition(), npcPos);
                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    idTo = m_wavePointsManager->aStar.GetClosestPoint(ent.GetGlobalPosition());
                }
            }
        }
        else
        {
            std::vector<Canis::Entity> towns = entity.GetEntitiesWithTag("TOWN");
            float closestDistance = std::numeric_limits<float>::max();
            glm::vec3 npcPos = entity.GetGlobalPosition();

            for (Canis::Entity &town : towns)
            {
                float dist = glm::distance(town.GetGlobalPosition(), npcPos);
                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    idTo = m_wavePointsManager->aStar.GetClosestPoint(town.GetGlobalPosition());
                }
            }
        }

        m_path = m_wavePointsManager->aStar.GetPath(idFrom, idTo);

        if (m_path.empty())
        {
            return;
        }
    }

    if (m_index >= m_path.size())
    {
        m_path.clear();
        return;
    }

    entity.GetComponent<NPCBoid>().target = m_path[m_index];

    if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
    {
        m_index++;
    }
}

Canis::Entity Enemy::GetClosestEnt()
{
    std::vector<Canis::Entity> ents = entity.GetEntitiesWithTag("ENT");

    Canis::Entity closestEnt;
    float closestDistance = std::numeric_limits<float>::max();
    glm::vec3 npcPos = entity.GetGlobalPosition();

    for (Canis::Entity &ent : ents)
    {
        float dist = glm::distance(ent.GetGlobalPosition(), npcPos);
        if (dist < closestDistance)
        {
            closestDistance = dist;
            closestEnt = ent;
        }
    }

    return closestEnt;
}