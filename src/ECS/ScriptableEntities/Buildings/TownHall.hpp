#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "../../Components/Health.hpp"

//Most important building && Spawns Inital Units
class TownHall : public Canis::ScriptableEntity
{
private:
    bool m_isAlive = false;
public:

    void OnCreate();
    
    void OnReady();

    void OnDestroy();

    void OnUpdate(float _dt);

    void SpawnUnit();
};