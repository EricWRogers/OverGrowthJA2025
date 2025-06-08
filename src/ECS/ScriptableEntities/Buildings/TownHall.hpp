#pragma once

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Systems/CollisionSystem.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>
#include "../../Components/Health.hpp"

//Most important building && Spawns Inital Units
class TownHall : public Canis::ScriptableEntity
{
private:
    bool m_isAlive = false;
    Canis::CollisionSystem* m_collisionSystem;
public:

    void OnCreate();
    
    void OnReady();

    void OnDestroy();

    void OnUpdate(float _dt);

    void SpawnUnit();
};