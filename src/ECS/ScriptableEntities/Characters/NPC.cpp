#include "NPC.hpp"
#include "../../Components/NPCBoid.hpp"

void NPC::OnCreate()
{
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = 25.0f;

    Health::ResetHealth(entity);

    Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    // Check Job
    if (characterClass == "Civilian")
    {
        ChangeCharacterClass("Worker");
    }

    Canis::Log("NPC is a " + characterClass);
}

void NPC::OnReady()
{
    entity.AddComponent<NPCBoid>();

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void NPC::OnUpdate(float _dt)
{
    GoToArea(_dt);
}

void NPC::ChangeCharacterClass(std::string _characterClass)
{
    characterClass = _characterClass;
}

void NPC::GoToArea(float _time)
{
    if (m_isWaiting)
    {
        m_counter += _time;
        if (m_counter >= m_waitTime)
        {
            m_counter = 0.0f;
            m_isWaiting = false;

            // Switch class after waiting
            if (characterClass == "Civilian")
                ChangeCharacterClass("Worker");
            else
                ChangeCharacterClass("Civilian");

            // Clear path so we recalculate next trip
            m_path.clear();
        }
        return; // stop doing path logic while waiting
    }

    if (m_path.size() == 0)
    {
        m_index = 0;

        int idFrom = wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
        int idTo = 0;

        if (characterClass == "Worker")
        {
            Canis::Entity farm = entity.GetEntityWithTag("FARM");
            idTo = wavePointsManager->aStar.GetClosestPoint(farm.GetGlobalPosition());
        }
        else if (characterClass == "Civilian")
        {
            Canis::Entity town = entity.GetEntityWithTag("TOWN");
            idTo = wavePointsManager->aStar.GetClosestPoint(town.GetGlobalPosition());
        }

        m_path = wavePointsManager->aStar.GetPath(idFrom, idTo);

        if (m_path.empty())
        {
            return;
        }
    }

    if (m_index >= m_path.size())
    {
        m_path.clear();
        m_isWaiting = true;
        return;
    }

    entity.GetComponent<NPCBoid>().target = m_path[m_index];

    if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
    {
        m_index++;
    }

    if (m_path.size() <= m_index)
    {
        m_path.clear();
        m_isWaiting = true;
    }
}