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

    Canis::SphereCollider &sphere = entity.GetComponent<Canis::SphereCollider>();

    sphere.layer = (unsigned int)Canis::BIT::THREE;
    sphere.mask = (unsigned int)Canis::BIT::TWO;

    m_collisionSystem = GetScene().GetSystem<Canis::CollisionSystem>();
}

void TownHall::OnReady()
{
    //Call the Spawn Inital Units
    SpawnUnit();
}

void TownHall::OnDestroy()
{
    Canis::Log("You Lose");
    entity.GetSceneManager().Load("lose_menu");
}

void TownHall::OnUpdate(float _dt)
{
    HealthComponent &health = entity.GetComponent<HealthComponent>();
    if(health.currentHealth == 0 && m_isAlive == true)
    {
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