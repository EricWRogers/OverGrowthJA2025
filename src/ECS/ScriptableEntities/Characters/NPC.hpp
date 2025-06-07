#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "WavePointsManager.hpp"
#include "../../Components/Health.hpp"

class NPC : public Canis::ScriptableEntity
{
private:
    bool m_isAlive = false;
    std::vector<glm::vec3> m_path;
    int m_currentPathIndex = 0;
    float m_moveSpeed = 2.0f;
public:
    std::string characterClass = "Civilian";
    WavePointsManager* wavePointsManager;

    void OnCreate();
    
    void OnReady();
    
    void OnDestroy() {}

    void OnUpdate(float _dt);

    void ChangeCharacterClass(std::string _characterClass);

    void GoToJob();

    void MoveNPC(float time);
};