#pragma once
#include <string>

#include <glm/gtx/rotate_vector.hpp>

#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/Transform.hpp>
#include <Canis/SceneManager.hpp>

#include <Canis/ECS/Components/Mesh.hpp>

class WavePointsManager : public Canis::ScriptableEntity
{
private:
    bool m_isVisable = true;
    int m_width = 20;
    int m_depth = 20;
public:
    void OnCreate();

    void OnReady() {}

    void OnUpdate(float _dt) {}

    void OnDestroy() {}
};