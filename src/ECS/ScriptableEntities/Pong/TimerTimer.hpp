#pragma once

#include <Canis/ScriptableEntity.hpp>

class TimerTimer2D : public Canis::ScriptableEntity
{
public:
    float counter = 10.0f;

    void OnCreate() {}
    void OnReady() {}
    void OnDestroy() {}
    void OnUpdate(float _dt);
};