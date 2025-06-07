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
}
    
void NPC::OnReady()
{

}
    
void NPC::OnDestroy()
{

}

void NPC::ChangeCharacterClass(std::string _characterClass)
{
    characterClass = _characterClass;
}

void NPC::GetJob()
{
    if(characterClass == "Civilian")
    {
        //NPC switches from doing nothing 
        ChangeCharacterClass("Worker");
        //Go To Job
    }
}

void NPC::GoToJob()
{
    
}