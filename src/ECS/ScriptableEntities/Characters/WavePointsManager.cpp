#include "WavePointsManager.hpp"


#include <Canis/ECS/Components/Color.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>

using namespace glm;
using namespace Canis;

void WavePointsManager::OnCreate() {
    for (int x = 0; x < m_width; x++)
    {
        for (int z = 0; z < m_depth; z++)
        {
            Entity wavePoint = CreateEntity();

            wavePoint.AddComponent<Transform>();
            wavePoint.SetParent(entity);
            wavePoint.SetPosition(vec3(x, 0.0f, z));
            wavePoint.SetScale(vec3(0.1f));

            if (m_isVisable)
            {
                wavePoint.AddComponent<SphereCollider>();
                wavePoint.AddComponent<Color>();
                Mesh& mesh = wavePoint.AddComponent<Mesh>();
                mesh.modelHandle.id = AssetManager::LoadModel("assets/models/white_block.obj");
                mesh.material = AssetManager::LoadMaterial("assets/materials/default.material");
            }
        }
    }
}