#include "NPC.hpp"
#include "../../Components/NPCBoid.hpp"
#include "../../Components/Billboard.hpp"
#include <Canis/ECS/Components/Sprite2DComponent.hpp>
#include <Canis/ECS/Components/SpriteAnimationComponent.hpp>
#include "../AI/AiBrain.hpp"

void NPC::OnCreate()
{
    if (!entity.HasComponent<HealthComponent>())
    {
        entity.AddComponent<HealthComponent>();
    }

    HealthComponent &health = entity.GetComponent<HealthComponent>();

    health.maxHealth = 25.0f;

    Health::ResetHealth(entity);

    Canis::Log("The Current Health is " + std::to_string(health.currentHealth));

    if (characterClass == "Civilian")
    {
        ChangeCharacterClass("Worker");
    }

    Canis::Log("NPC is a " + characterClass);
}

void NPC::OnReady()
{
    Canis::Entity brainEntity = entity.GetEntityWithTag("AI_BRAIN");
    aiBrain = &brainEntity.GetScript<AiBrain>();

    entity.AddComponent<NPCBoid>();
    entity.AddComponent<Billboard>();
    Canis::Sprite2DComponent& sc = entity.AddComponent<Canis::Sprite2DComponent>();
    sc.textureHandle = Canis::AssetManager::GetTextureHandle("assets/textures/civilian/civilian_build.png");
    
    Canis::SpriteAnimationComponent& sac = entity.AddComponent<Canis::SpriteAnimationComponent>();
    sac.Play("assets/animations/civilian_build.anim");
    sac.flipX = false; 

    Canis::Entity manager = entity.GetEntityWithTag("GRIDLAYOUT");
    wavePointsManager = &manager.GetScript<WavePointsManager>();
}

void NPC::OnUpdate(float _dt)
{
    Canis::Sprite2DComponent& sc = entity.GetComponent<Canis::Sprite2DComponent>();
    Canis::Mesh& mesh = entity.GetComponent<Canis::Mesh>();
    mesh.albedoIdOverride = sc.textureHandle.id;
    mesh.overrideMaterialField = true;
    mesh.overrideMaterialFields.SetFloat("uvx", sc.uv.x);
    mesh.overrideMaterialFields.SetFloat("uvy", sc.uv.y);
    mesh.overrideMaterialFields.SetFloat("uvw", sc.uv.z);
    mesh.overrideMaterialFields.SetFloat("uvh", sc.uv.w);
    
    if (!hasJob && aiBrain != nullptr)
{
    hasJob = aiBrain->RequestJob(this, currentJob); 
    if (hasJob)
        m_index = 0;
}

if (hasJob)
{
    if (m_index >= currentJob.path.size())
    {
        aiBrain->CompleteJob(currentJob);
        hasJob = false;
        currentJob.path.clear();
    }
    else
    {
        entity.GetComponent<NPCBoid>().target = currentJob.path[m_index];

        if (glm::distance(currentJob.path[m_index], entity.GetGlobalPosition()) < 0.8f)
            m_index++;
    }
}
else
{
    GoToArea(_dt);
}

}

void NPC::ChangeCharacterClass(std::string _characterClass)
{
    characterClass = _characterClass;
    entity.SetTag(characterClass);
}

void NPC::GoToArea(float _time)
{
    if (m_isWaiting)
    {
        //SetAnimation("assets/animations/civilian_build.anim", false);

        m_counter += _time;
        if (m_counter >= m_waitTime)
        {
            m_counter = 0.0f;
            m_isWaiting = false;

            if (characterClass == "Civilian")
            {
                //Play animation
                ChangeCharacterClass("Worker");
            }
            else
            {
                //Play animation
                ChangeCharacterClass("Civilian"); 
            }

            m_path.clear();
        }
        return;
    }

    if (m_path.size() == 0)
    {
        m_index = 0;

        int idFrom = wavePointsManager->aStar.GetClosestPoint(entity.GetGlobalPosition());
        int idTo = 0;

        if (characterClass == "Worker")
        {
            std::vector<Canis::Entity> farms = entity.GetEntitiesWithTag("FARM");
            float closestDistance = std::numeric_limits<float>::max();
            glm::vec3 npcPos = entity.GetGlobalPosition();

            for (Canis::Entity &farm : farms)
            {
                float dist = glm::distance(farm.GetGlobalPosition(), npcPos);
                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    idTo = wavePointsManager->aStar.GetClosestPoint(farm.GetGlobalPosition());
                }
            }
        }
        else if (characterClass == "Civilian")
        {
            std::vector<Canis::Entity> towns = entity.GetEntitiesWithTag("TOWN");
            float closestDistance = std::numeric_limits<float>::max();
            glm::vec3 npcPos = entity.GetGlobalPosition();

            for (Canis::Entity &town : towns)
            {
                float dist = glm::distance(town.GetGlobalPosition(), npcPos);
                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    idTo = wavePointsManager->aStar.GetClosestPoint(town.GetGlobalPosition());
                }
            }
        }


        m_path = wavePointsManager->aStar.GetPath(idFrom, idTo);

        if (m_path.empty())
        {
            return;
        }
    }

    if (m_index >= m_path.size())
    {
        m_path.clear();
        m_isWaiting = true;
        return;
    }

    // glm::vec3 dir = m_path[m_index] - entity.GetGlobalPosition();
    // bool facingBack = dir.z > 0.0f;

    // if (facingBack)
    //     SetAnimation("assets/animations/civilian_walk_back.anim", false);
    // else
    //     SetAnimation("assets/animations/civilian_walk_back.anim", false);

    entity.GetComponent<NPCBoid>().target = m_path[m_index];

    if (glm::distance(m_path[m_index], entity.GetGlobalPosition()) < 0.8f)
    {
        m_index++;
    }

    if (m_path.size() <= m_index)
    {
        m_path.clear();
        m_isWaiting = true;
    }
}

void NPC::SetAnimation(std::string _path, bool _flipX = false)
{
    auto& anim = entity.GetComponent<Canis::SpriteAnimationComponent>();
    anim.Play(_path);
    anim.flipX = _flipX;
}