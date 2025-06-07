#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "../../Components/Health.hpp"

class NPC : public Canis::ScriptableEntity
{
private:
    bool m_isAlive = false;
public:
    std::string characterClass = "Civilian";

    void OnCreate();
    
    void OnReady();
    
    void OnDestroy();

    void ChangeCharacterClass(std::string _characterClass);

    void GetJob();

    void GoToJob();
};