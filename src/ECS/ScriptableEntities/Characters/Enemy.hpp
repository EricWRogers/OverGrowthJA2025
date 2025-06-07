#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "../../Components/Health.hpp"

class Enemy : public Canis::ScriptableEntity
{
private:
    bool isAlive = false;
public:

    void OnCreate();
    
    void OnReady() {}
    
    void OnDestroy();

};