#include "DummyNPC.hpp"
#include "../../Components/NPCBoid.hpp"

void DummyNPC::OnReady()
{
    entity.AddComponent<NPCBoid>();

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    m_wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void DummyNPC::OnUpdate(float _dt)
{
    if (m_path.size() == 0)
    {
        m_index = 0;

        int idFrom = m_wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
        int idTo = 0;
        
        if (m_goToFarm)
        {
            m_goToFarm = false;
            Canis::Entity farm = entity.GetEntityWithTag("FARM");
            idTo = m_wavePointsManager->aStar.GetClosestPoint(farm.GetGlobalPosition());
        }
        else
        {
            m_goToFarm = true;
            Canis::Entity town = entity.GetEntityWithTag("TOWN");
            idTo = m_wavePointsManager->aStar.GetClosestPoint(town.GetGlobalPosition());
        }

        m_path = m_wavePointsManager->aStar.GetPath(idFrom, idTo);
    }

    entity.GetComponent<NPCBoid>().target = m_path[m_index];

    if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
        m_index++;

    if (m_path.size() <= m_index)
        m_path.clear();
}