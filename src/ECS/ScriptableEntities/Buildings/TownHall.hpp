#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "../../Components/Health.hpp"

//Most important building && Spawns Inital Units
class TownHall
{
private:

public:
    void OnCreate();
    
    void OnReady();

    void OnDestroy();

    void SpawnUnit();
};