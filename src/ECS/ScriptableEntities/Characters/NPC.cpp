#include "NPC.hpp"

void NPC::OnCreate()
{
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = 25.0f;

    Health::ResetHealth(entity);

    m_isAlive = true;

    Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    //Check Job
    if(characterClass == "Civilian")
    {
        //NPC switches from doing nothing 
        ChangeCharacterClass("Worker");
        //Go To Job
    }

    Canis::Log("NPC is a " + characterClass);
}
    
void NPC::OnReady()
{
    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    wavePointsManager = &manager.GetScript<WavePointsManager>();
}
    
void NPC::OnDestroy()
{
    //Unassign anything else
}

void NPC::ChangeCharacterClass(std::string _characterClass)
{
    characterClass = _characterClass;
}

void NPC::GoToJob()
{
    int idFrom = wavePointsManager->aStar.GetClosestPoint(glm::vec3(0.0f));
    int idTo = wavePointsManager->aStar.GetClosestPoint(glm::vec3(10.0f,0.0f,10.0f));
    wavePointsManager->aStar.GetPath(idFrom, idTo);
}