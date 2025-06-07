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
}

void Enemy::OnReady()
{
    entity.AddComponent<NPCBoid>();

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    m_wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void Enemy::OnUpdate(float _dt)
{

}

void Enemy::Attack(Canis::Entity _target)
{
    
}

void Enemy::GoTo()
{
    if (m_path.size() == 0)
    {
        m_index = 0;

        int idFrom = m_wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
        int idTo = 0;

        Canis::Entity ent = entity.GetEntityWithTag("ENT");
        idTo = m_wavePointsManager->aStar.GetClosestPoint(ent.GetGlobalPosition());

        Canis::Entity town = entity.GetEntityWithTag("TOWN");
        idTo = m_wavePointsManager->aStar.GetClosestPoint(town.GetGlobalPosition());

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