#pragma once

#include <Canis/ScriptableEntity.hpp>

class Sapling : public Canis::ScriptableEntity
{
public:
    float counter = 0.0f;
    float startTime = 10.0f;

    void OnCreate();
    void OnReady() {}
    void OnDestroy() {}
    void OnUpdate(float _dt);
    void ChangeModel();
};