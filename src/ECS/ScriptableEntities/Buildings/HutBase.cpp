#include "HutBase.hpp"
#include "../AI/AiBrain.hpp" 
void HutBase::OnCreate()
{
    current_health = max_health;
    counter = job_creation_interval;
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = current_health;

    Health::ResetHealth(entity);

    m_isAlive = true;

    Canis::Log("New Building created. HUT");
}

void HutBase::OnReady()
{
    //Not sure we should do anything there.
    //SpawnUnit();
}

void HutBase::OnDestroy()
{
    Canis::Log("Building Destroyed");
   
}


void HutBase::OnUpdate(float _dt)
{
    //  counter -= _dt;

    // if (counter < 0.0f)
    // {
    //     counter = create_resource_interval;
    //     AllocateResource();
    // }
        
    counter -= _dt;
    if (counter <= 0.0f)
    {
        counter = job_creation_interval;

        if (aiBrain)
        {
            Job newJob(this, jobPositions, jobPriority);
            aiBrain->AddJob(newJob);
        }
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();
    if(health.currentHealth == 0 && m_isAlive == true)
    {
        
        entity.Destroy();
        
    }

    // if(GetInputManager().JustPressedKey(SDLK_e))
    // {
    //     Canis::Log("Button Pressed");
    //     Health::Annihilation(entity);
    // }
}

void HutBase::AllocateResource()
{
    Canis::Log("Allocating Resource");
}