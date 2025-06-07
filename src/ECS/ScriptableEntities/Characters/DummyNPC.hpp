#pragma once

#include <Canis/ScriptableEntity.hpp>

class DummyNPC : public Canis::ScriptableEntity
{
private:
public:

    void OnCreate() {}
    void OnReady();
    void OnDestroy() {}
    void OnUpdate(float _dt);
};