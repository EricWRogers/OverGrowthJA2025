#include "TownHall.hpp"

void TownHall::OnCreate()
{
    //Set Town Hall Max Health
    m_healthComponent.maxHealth = 25.0f;
    Health::ResetHealth(m_entity);
}

void TownHall::OnReady()
{
    //Call the Spawn Inital Units
    SpawnUnit();
}

void TownHall::OnDestroy()
{
    //Lose Game Screen
}

void TownHall::SpawnUnit()
{

}