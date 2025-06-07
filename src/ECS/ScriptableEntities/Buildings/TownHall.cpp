#include "TownHall.hpp"

void TownHall::OnCreate()
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

void TownHall::OnReady()
{
    //Call the Spawn Inital Units
    SpawnUnit();
}

void TownHall::OnDestroy()
{
    //Lose Game Screen
    Canis::Log("No Dont destroy");
    entity.GetSceneManager().Load("lose_menu");
}

void TownHall::OnUpdate(float _dt)
{
    HealthComponent &health = entity.GetComponent<HealthComponent>();
    if(health.currentHealth == 0 && m_isAlive == true)
    {
        Canis::Log("You Lose");
        entity.Destroy();
    }

    if(GetInputManager().JustPressedKey(SDLK_e))
    {
        Canis::Log("Button Pressed");
        Health::Annihilation(entity);
    }
}

void TownHall::SpawnUnit()
{
    Canis::Log("Spawning Units");
}