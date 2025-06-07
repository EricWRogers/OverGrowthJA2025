#pragma once

#include <Canis/ScriptableEntity.hpp>

class Sapling : public Canis::ScriptableEntity
{
public:
    float counter = 0.0f;
    float startTime = 2.0f;
    float maxSize = 2.0f;
    bool stop = false;

    void OnCreate();
    void OnReady() {}
    void OnDestroy() {}
    void OnUpdate(float _dt);
    void ChangeModel();
};