#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "../../Components/Health.hpp"

class NPC : public Canis::ScriptableEntity
{
private:
    Canis::Entity m_entity;
    HealthComponent m_healthComponent;
public:
    std::string characterClass = "Civilian";

    void OnCreate();
    
    void OnReady();
    
    void OnDestroy();

    void ChangeCharacterClass(std::string _characterClass);

    void GetJob();
};