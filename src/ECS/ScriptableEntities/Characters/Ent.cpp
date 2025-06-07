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
    // if (m_path.empty())
    // {
    //     m_index = 0;

    //     glm::vec3 currentPos = entity.GetGlobalPosition();
    //     int idFrom = m_wavePointsManager->aStar.GetClosestPoint(currentPos);

        
    //     std::vector<int> nearbyNodeIDs;
    //     float roamRadius = 5.0f;

    //     for (int i = 0; i < m_wavePointsManager->aStar.points.size(); i++)
    //     {
    //         if (i == idFrom)
    //             continue;

    //         const glm::vec3& point = m_wavePointsManager->aStar.points[i];
    //         if (glm::distance(currentPos, point) <= roamRadius)
    //         {
    //             nearbyNodeIDs.push_back(i);
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