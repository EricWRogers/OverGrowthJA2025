#include "Ent.hpp"
#include "../../Components/NPCBoid.hpp"

void Ent::OnCreate()
{

}

void Ent::OnReady()
{
    
}

void Ent::OnUpdate(float _dt)
{
    if(m_enemyWaveStarted)
    {
        MoveToAttack();
    }else
    {
        Roam();
    }
}

void Ent::Attack()
{

}

void Ent::MoveToAttack()
{
    Canis::Log("Enemies Have Been Spotted Defend");
}

void Ent::Roam()
{
    Canis::Log("Nothing going on here");
    if (m_path.empty())
    {
        m_index = 0;

        glm::vec3 currentPos = entity.GetGlobalPosition();
        int idFrom = m_wavePointsManager->aStar.GetClosestPoint(currentPos);

        std::vector<int> nearbyNodeIDs;
        float roamRadius = 5.0f;

        // Try random directions around the entity
        for (int i = 0; i < 20; ++i) // 20 random samples
        {
            float angle = glm::radians((float)(rand() % 360));
            glm::vec3 offset = glm::vec3(cos(angle), 0.0f, sin(angle)) * roamRadius * ((rand() % 100) / 100.0f);
            glm::vec3 samplePos = currentPos + offset;

            if (!m_wavePointsManager->aStar.ValidPoint(samplePos))
            {
                continue;
            }

            int id = m_wavePointsManager->aStar.GetClosestPoint(samplePos);

            if (id != idFrom)
            {
                nearbyNodeIDs.push_back(id);
            }
        }

        if (nearbyNodeIDs.empty())
        {
            return;
        }

        int idTo = nearbyNodeIDs[rand() % nearbyNodeIDs.size()];
        m_path = m_wavePointsManager->aStar.GetPath(idFrom, idTo);

        if (m_path.empty())
        {
            return;
        }
    }

    if (m_index >= m_path.size())
    {
        return;
    }

    entity.GetComponent<NPCBoid>().target = m_path[m_index];

    if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
    {
        m_index++;
    }
}