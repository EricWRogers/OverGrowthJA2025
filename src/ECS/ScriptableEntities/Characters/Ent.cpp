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
}