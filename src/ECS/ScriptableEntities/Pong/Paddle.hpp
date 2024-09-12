#pragma once

#include <Canis/ScriptableEntity.hpp>

class Paddle : public Canis::ScriptableEntity
{
private:
    float m_speed = 400.0f;
    
public:
    bool left = false;
    bool right = false;

    void OnCreate();
    void OnReady() {}
    void OnDestroy() {}
    void OnUpdate(float _dt);
};