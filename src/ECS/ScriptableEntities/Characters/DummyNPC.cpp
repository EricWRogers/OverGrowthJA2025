#include "DummyNPC.hpp"
#include "../../Components/NPCBoid.hpp"
#include "../../Components/Billboard.hpp"
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/SpriteAnimationComponent.hpp>

void DummyNPC::OnReady()
{
    entity.AddComponent<NPCBoid>();
    entity.AddComponent<Billboard>();
    Canis::Sprite2DComponent& sc = entity.AddComponent<Canis::Sprite2DComponent>();
    sc.textureHandle = Canis::AssetManager::GetTextureHandle("assets/textures/civilian/civilian_build.png");
    
    Canis::SpriteAnimationComponent& sac = entity.AddComponent<Canis::SpriteAnimationComponent>();
    sac.Play("assets/animations/civilian_build.anim");
    sac.flipX = false; 

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    m_wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void DummyNPC::OnUpdate(float _dt)
{
    Canis::Sprite2DComponent& sc = entity.GetComponent<Canis::Sprite2DComponent>();
    Canis::Mesh& mesh = entity.GetComponent<Canis::Mesh>();
    mesh.albedoIdOverride = sc.textureHandle.id;
    mesh.overrideMaterialField = true;
    mesh.overrideMaterialFields.SetFloat("uvx", sc.uv.x);
    mesh.overrideMaterialFields.SetFloat("uvy", sc.uv.y);
    mesh.overrideMaterialFields.SetFloat("uvw", sc.uv.z);
    mesh.overrideMaterialFields.SetFloat("uvh", sc.uv.w);

    //Canis::Log(glm::to_string(sc.uv));

    if (m_path.size() == 0)
    {
        m_index = 0;

        int idFrom = m_wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
        int idTo = 0;
        
        if (m_goToFarm)
        {
            m_goToFarm = false;
            Canis::Entity farm = entity.GetEntityWithTag("FARM");
            idTo = m_wavePointsManager->aStar.GetClosestPoint(farm.GetGlobalPosition());
        }
        else
        {
            m_goToFarm = true;
            Canis::Entity town = entity.GetEntityWithTag("TOWN");
            idTo = m_wavePointsManager->aStar.GetClosestPoint(town.GetGlobalPosition());
        }

        m_path = m_wavePointsManager->aStar.GetPath(idFrom, idTo);
    }

    entity.GetComponent<NPCBoid>().target = m_path[m_index];

    if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
        m_index++;

    if (m_path.size() <= m_index)
        m_path.clear();
}