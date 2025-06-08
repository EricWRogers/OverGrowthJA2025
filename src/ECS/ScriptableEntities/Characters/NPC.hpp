#pragma once

#include <Canis/ScriptableEntity.hpp>
#include "WavePointsManager.hpp"
#include "../../Components/Health.hpp"

class NPC : public Canis::ScriptableEntity
{
private:
    std::vector<glm::vec3> m_path = {};
    float m_counter = 0.0f;
    float m_waitTime = 2.0f;
    int m_index = 0;
    bool m_isWaiting = false;
public:
    std::string characterClass = "Civilian";
    WavePointsManager* wavePointsManager;

    void OnCreate();
    
    void OnReady();
    
    void OnDestroy() {}

    void OnUpdate(float _dt);

    void ChangeCharacterClass(std::string _characterClass);

    void GoToArea(float _time);

    void SetAnimation(std::string _path, bool _flipX);
};