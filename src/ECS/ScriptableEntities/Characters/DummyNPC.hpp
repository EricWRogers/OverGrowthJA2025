#pragma once

#include "WavePointsManager.hpp"
#include <Canis/ScriptableEntity.hpp>

class DummyNPC : public Canis::ScriptableEntity
{
private:
    int m_index = 0;
    std::vector<glm::vec3> m_path = {};
    WavePointsManager* m_wavePointsManager;
    bool m_goToFarm = false;
    float m_counter = 1.0f;
    float m_waitTime = 0.2f;
public:

    void OnCreate() {}
    void OnReady();
    void OnDestroy() {}
    void OnUpdate(float _dt);
};