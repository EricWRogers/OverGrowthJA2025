#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "WavePointsManager.hpp"
#include "../../Components/Health.hpp"

class NPC : public Canis::ScriptableEntity
{
private:
    bool m_isAlive = false;
public:
    std::string characterClass = "Civilian";
    WavePointsManager* wavePointsManager;

    void OnCreate();
    
    void OnReady();
    
    void OnDestroy();

    void ChangeCharacterClass(std::string _characterClass);

    void GoToJob();
};