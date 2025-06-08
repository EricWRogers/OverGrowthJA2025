#pragma once
#include <string>

#include <glm/gtx/rotate_vector.hpp>

#include <Canis/Math.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/Transform.hpp>
#include <Canis/SceneManager.hpp>

#include <Canis/ECS/Components/Mesh.hpp>

#include <Canis/GameHelper/AStar.hpp>

class WavePointsManager : public Canis::ScriptableEntity
{
private:
    bool m_isVisable = false;
    int m_width = 100;
    int m_depth = 100;
    int m_defaultHeight = 0.0f;
public:
    Canis::AStar aStar;

    void OnCreate();

    void OnReady();

    void OnUpdate(float _dt) {}

    void OnDestroy() {}
};