#include "WavePointsManager.hpp"


#include <Canis/ECS/Components/Color.hpp>
#include <Canis/ECS/Components/SphereCollider.hpp>

using namespace glm;
using namespace Canis;

void WavePointsManager::OnCreate() {
    Transform& transform = entity.GetComponent<Transform>();

    // place wave points
    for (int x = 0; x < m_width; x++)
    {
        for (int z = 0; z < m_depth; z++)
        {
            Entity wavePoint = CreateEntity();

            wavePoint.AddComponent<Transform>();
            wavePoint.SetParent(entity);
            wavePoint.SetPosition(vec3(x, m_defaultHeight, z));
            wavePoint.SetScale(vec3(0.1f));

            if (m_isVisable)
            {
                wavePoint.AddComponent<SphereCollider>();
                wavePoint.AddComponent<Color>();
                Mesh& mesh = wavePoint.AddComponent<Mesh>();
                mesh.modelHandle.id = AssetManager::LoadModel("assets/models/white_block.obj");
                mesh.material = AssetManager::LoadMaterial("assets/materials/default.material");
            }

            aStar.AddPoint(wavePoint.GetGlobalPosition());
        }
    }

    // connect wave points
    for (int x = 0; x < m_width; x++)
    {
        for (int z = 0; z < m_depth; z++)
        {
            if (aStar.ValidPoint(vec3(x, transform.position.y + m_defaultHeight, z)))
            {
                for (int xOffset = -1; xOffset < 2; xOffset++)
                {
                    for (int zOffset = -1; zOffset < 2; zOffset++)
                    {
                        float y = transform.position.y + m_defaultHeight;
                        if (aStar.ValidPoint(vec3(x + xOffset, y, z + zOffset)))
                        {
                            if (vec3(x + xOffset, y, z + zOffset) == vec3(0.0f, 0.0f, 0.0f))
                                continue;

                            if (xOffset == 0.0f || zOffset == 0.0f)
                            {
                                aStar.ConnectPoints(
                                    aStar.GetPointByPosition(vec3(x + xOffset, y, z + zOffset)),
                                    aStar.GetPointByPosition(vec3(x, y, z)));
                            }
                        }
                    }
                }
            }
        }
    }
}